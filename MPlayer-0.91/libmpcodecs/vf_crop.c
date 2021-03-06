#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../mp_msg.h"

#include "img_format.h"
#include "mp_image.h"
#include "vf.h"

struct vf_priv_s {
    int crop_w,crop_h;
    int crop_x,crop_y;
};

extern int opt_screen_size_x;
extern int opt_screen_size_y;

//===========================================================================//

static int config(struct vf_instance_s* vf,
        int width, int height, int d_width, int d_height,
	unsigned int flags, unsigned int outfmt){
    // calculate the missing parameters:
    if(vf->priv->crop_w<=0 || vf->priv->crop_w>width) vf->priv->crop_w=width;
    if(vf->priv->crop_h<=0 || vf->priv->crop_h>height) vf->priv->crop_h=height;
    if(vf->priv->crop_x<0) vf->priv->crop_x=(width-vf->priv->crop_w)/2;
    if(vf->priv->crop_y<0) vf->priv->crop_y=(height-vf->priv->crop_h)/2;
    // rounding:
    if(!IMGFMT_IS_RGB(outfmt) && !IMGFMT_IS_BGR(outfmt)){
	switch(outfmt){
	case IMGFMT_444P:
	case IMGFMT_Y800:
	case IMGFMT_Y8:
	    break;
	case IMGFMT_YVU9:
	case IMGFMT_IF09:
	    vf->priv->crop_y&=~3;
	case IMGFMT_411P:
	    vf->priv->crop_x&=~3;
	    break;
	case IMGFMT_YV12:
	case IMGFMT_I420:
	case IMGFMT_IYUV:
	    vf->priv->crop_y&=~1;
	default:
	    vf->priv->crop_x&=~1;
	}
    }
    // check:
    if(vf->priv->crop_w+vf->priv->crop_x>width ||
       vf->priv->crop_h+vf->priv->crop_y>height){
	printf("crop: bad position/width/height - cropped area is out of the original!\n");
	return 0;
    }
    if(!opt_screen_size_x && !opt_screen_size_y){
	d_width=d_width*vf->priv->crop_w/width;
	d_height=d_height*vf->priv->crop_h/height;
    }
    return vf_next_config(vf,vf->priv->crop_w,vf->priv->crop_h,d_width,d_height,flags,outfmt);
}

static int put_image(struct vf_instance_s* vf, mp_image_t *mpi){
    mp_image_t *dmpi=vf_get_image(vf->next,mpi->imgfmt,
	MP_IMGTYPE_EXPORT, 0,
	vf->priv->crop_w, vf->priv->crop_h);
    if(mpi->flags&MP_IMGFLAG_PLANAR){
	dmpi->planes[0]=mpi->planes[0]+
	    vf->priv->crop_y*mpi->stride[0]+vf->priv->crop_x;
	dmpi->planes[1]=mpi->planes[1]+
	    (vf->priv->crop_y>>mpi->chroma_y_shift)*mpi->stride[1]+(vf->priv->crop_x>>mpi->chroma_x_shift);
	dmpi->planes[2]=mpi->planes[2]+
	    (vf->priv->crop_y>>mpi->chroma_y_shift)*mpi->stride[2]+(vf->priv->crop_x>>mpi->chroma_x_shift);
	dmpi->stride[1]=mpi->stride[1];
	dmpi->stride[2]=mpi->stride[2];
    } else {
	dmpi->planes[0]=mpi->planes[0]+
	    vf->priv->crop_y*mpi->stride[0]+
	    vf->priv->crop_x*(mpi->bpp/8);
	dmpi->planes[1]=mpi->planes[1]; // passthrough rgb8 palette
    }
    dmpi->stride[0]=mpi->stride[0];
    dmpi->width=mpi->width;
    return vf_next_put_image(vf,dmpi);
}

//===========================================================================//

static int open(vf_instance_t *vf, char* args){
    vf->config=config;
    vf->put_image=put_image;
    vf->default_reqs=VFCAP_ACCEPT_STRIDE;
    vf->priv=malloc(sizeof(struct vf_priv_s));
    // TODO: parse args ->
    vf->priv->crop_x=
    vf->priv->crop_y=
    vf->priv->crop_w=
    vf->priv->crop_h=-1;
    if(args) sscanf(args, "%d:%d:%d:%d", 
    &vf->priv->crop_w,
    &vf->priv->crop_h,
    &vf->priv->crop_x,
    &vf->priv->crop_y);
    mp_msg(MSGT_VFILTER, MSGL_INFO, "Crop: %d x %d, %d ; %d\n",
    vf->priv->crop_w,
    vf->priv->crop_h,
    vf->priv->crop_x,
    vf->priv->crop_y);
    return 1;
}

vf_info_t vf_info_crop = {
    "cropping",
    "crop",
    "A'rpi",
    "",
    open
};

//===========================================================================//
