#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

#include "../vidix.h"
#include "../fourcc.h"
#include "../../config.h"
#include "w100api_fake.h"

static uint16_t g_overlayHandle;

static uint32_t VRAMoffset;
static uint16_t VH;

static uint32_t VRAMoffset2;
static uint16_t VH2;

static vidix_playback_t st_playbackInfo;

static vidix_capability_t w100_cap =
{
    "ATI Imageon 100 (W100) driver",
    "Alexander Chukov <sash@cacko.biz>",
    TYPE_OUTPUT,
    { 0, 0, 0, 0 },                     /* reserved */
    480,                       /* max width */
    640,                      /* max height */
    4,                                  /* min width */
    4,                                  /* min height */
    -1,                                 /* max framerate */
    FLAG_EQUALIZER,                     /* flags */
    0x1002,                             /* VENDOR_ATI(libdha/pci_vendors.h) */
    -1,                                 /* device id */
    { 0, 0, 0, 0 }                      /* reserved */
};

unsigned int vixGetVersion(void)
{
    return VIDIX_VERSION;
}

int vixProbe(int verbose, int force)
{
    return 0;
}

int vixInit(void)
{
    if (AtiCore_ProcessAttach()) {
        if (AtiCore_AllocOverlay(&g_overlayHandle)) {
	    VH = VH2 = 0;
            return 0;
	}
    }

    return ENOSYS;
}

void vixDestroy(void)
{
    AtiCore_SetOverlayOnOff(g_overlayHandle, 0);
    if (VH2) AtiCore_DestroySurface(VH2);
    if (VH) AtiCore_DestroySurface(VH);
    AtiCore_ReleaseOverlay(g_overlayHandle);
    AtiCore_ProcessDetach();
}

int vixGetCapability(vidix_capability_t *to)
{
    memcpy(to, &w100_cap, sizeof(vidix_capability_t));
    return 0;
}

static int is_supported_fourcc(uint32_t fourcc)
{
    switch(fourcc) {
    case IMGFMT_YV12:
        return 1;
    default:
        return 0;
    }
}

int vixQueryFourcc(vidix_fourcc_t *to)
{
    if (is_supported_fourcc(to->fourcc)) {
        to->depth = VID_DEPTH_1BPP | VID_DEPTH_2BPP |
            VID_DEPTH_4BPP | VID_DEPTH_8BPP |
            VID_DEPTH_12BPP| VID_DEPTH_15BPP|
            VID_DEPTH_16BPP| VID_DEPTH_24BPP|
            VID_DEPTH_32BPP;
        to->flags = VID_CAP_EXPAND | VID_CAP_SHRINK;
/*         to->flags = VID_CAP_EXPAND | VID_CAP_SHRINK | VID_CAP_COLORKEY; */
        return 0;
    } else
        to->depth = to->flags = 0;

    return ENOSYS;
}

int vixGetGrKeys(vidix_grkey_t *grkey)
{
    return 0;
}

int vixSetGrKeys(const vidix_grkey_t *grkey)
{
    return 0;
}

static vidix_video_eq_t st_equal =
{
    VEQ_CAP_BRIGHTNESS,
    0, 0, 0, 0, 0, 0, 0, 0
};

int vixPlaybackGetEq(vidix_video_eq_t * eq)
{
    memcpy(eq, &st_equal, sizeof(st_equal));
    return 0;
}

int vixPlaybackSetEq(const vidix_video_eq_t * eq)
{
    int br;

    if (eq->cap & VEQ_CAP_BRIGHTNESS)
        st_equal.brightness = eq->brightness;
    if (eq->cap & VEQ_CAP_CONTRAST)
        st_equal.contrast = eq->contrast;
    if (eq->cap & VEQ_CAP_SATURATION)
        st_equal.saturation = eq->saturation;
    if (eq->cap & VEQ_CAP_HUE)
        st_equal.hue = eq->hue;
    if (eq->cap & VEQ_CAP_RGB_INTENSITY) {
        st_equal.red_intensity   = eq->red_intensity;
        st_equal.green_intensity = eq->green_intensity;
        st_equal.blue_intensity  = eq->blue_intensity;
    }
    st_equal.flags = eq->flags;

    br = (st_equal.brightness + 1000) * 127 / 2000;
    if (br < 0)
        br = 0;
    if (br > 127)
        br = 127;
    if (br > 64)
        br -= 64;
    else
        br += 64;

    AtiCore_SetDisplayBrightness(br);

    return 0;
}

int vixConfigPlayback(vidix_playback_t *info)
{
    int src_w, src_h;
    int drw_w, drw_h;
    int y_pitch, uv_pitch;
    int i, ret;
    ATI_OVERLAYPROP overlayProp;
    ATI_CLIPRECT clipRect;
    uint32_t regdata, base;
    uint32_t intAddr, extAddr, isExt = 0;

    if (!is_supported_fourcc(info->fourcc))
        return -1;

    src_w = info->src.w;
    src_h = info->src.h;
    drw_w = info->dest.w;
    drw_h = info->dest.h;    

    switch (info->fourcc) {
	case IMGFMT_YV12:
	    y_pitch = (src_w + 15) & ~15;
	    uv_pitch = ((src_w / 2) + 7) & ~7;
	    info->offset.y = 0;
	    info->offset.v = y_pitch * src_h;
	    info->offset.u = info->offset.v + uv_pitch * (src_h / 2);
	    info->frame_size = y_pitch * src_h + 2 * uv_pitch * (src_h / 2);
	    break;
	default:
	    return -1;
    }

/*
    {
	int extm, intm;
	
	GetAvailableVideoMem(&intm, &extm);
	fprintf(stderr, "internal memory = %d\n"
			"external memory = %d\n",
			intm, extm);
    }
 */

#ifdef DEBUG
    fprintf(stderr, "w100_vid: struct info {\n");
    fprintf(stderr, "w100_vid:   src.x:%d. src.y:%d. src.w:%d, src.h:%d,\n",
            info->src.x, info->src.y, info->src.w, info->src.h);
    fprintf(stderr, "w100_vid:   dest.x:%d. dest.y:%d. dest.w:%d, dest.h:%d,\n",
            info->dest.x, info->dest.y, info->dest.w, info->dest.h);
    fprintf(stderr, "w100_vid:   offset.y:%d, offset.v:%d offset.y:%d\n",
            info->offset.y, info->offset.v, info->offset.u);
    fprintf(stderr, "w100_vid:   frame_size:%d,\n", info->frame_size);
#endif

    if (AtiCore_AllocateSurface( &VH, &VRAMoffset, info->frame_size, 0 )) {
#ifdef DEBUG
	fprintf(stderr, "w100_vid:   main overlay surface offset = 0x%08x.\n", VRAMoffset);
#endif
    } else {
#ifdef DEBUG
	fprintf(stderr, "w100_vid:   cannot allocate main overlay surface.\n");
#endif
	return -1;
    }

    AtiCore_SetupMemoryTransfer(VRAMoffset, &intAddr);
    AtiCore_TerminateMemoryTransfer();

    if (info->num_frames == 1) {
        info->dga_addr = (void *)(intAddr);
    } else {
	if (AtiCore_AllocateSurface( &VH2, &VRAMoffset2, info->frame_size, 0 )) {
#ifdef DEBUG
	    fprintf(stderr, "w100_vid:   shadow overlay surface offset = 0x%08x.\n", VRAMoffset2);
#endif
	} else {
#ifdef DEBUG
	    fprintf(stderr, "w100_vid:   cannot allocate shadow overlay surface.\n");
#endif
	    return -1;
	}

	AtiCore_SetupMemoryTransfer(VRAMoffset, &extAddr);
	AtiCore_TerminateMemoryTransfer();

        if (info->num_frames > 1) /* no more ATI onchip memory */
            info->num_frames = 1;
        info->dga_addr = (void *)(extAddr);
    }
#ifdef DEBUG
    fprintf(stderr, "w100_vid:   num_frames:%d,\n", info->num_frames);
#endif
    info->dest.pitch.y = 16;
    info->dest.pitch.u = 16;
    info->dest.pitch.v = 16;
#ifdef DEBUG
    fprintf(stderr, "w100_vid: }\n");
    fprintf(stderr, "w100_vid: 0x%08x\n", (uint32_t)info->dga_addr);
#endif
    info->offsets[0] = 0;

    overlayProp.lpSrcBitmap = (uint32_t *)VRAMoffset;
    overlayProp.XCoord = 0;
    overlayProp.YCoord = 0;
    overlayProp.SrcPitch = y_pitch;
    overlayProp.SrcHeight = src_h;
    overlayProp.OverlayWidth = y_pitch;
    overlayProp.OverlayHeight = src_h;
    overlayProp.lpOverlayKey = 0;
    overlayProp.OverlayFormat = OVLTYPE_YUV420;

    ret = AtiCore_SetupOverlay(g_overlayHandle, &overlayProp);
#ifdef DEBUG
    printf("w100_vid: AtiCore_SetupOverlay: ret=%d\n", ret);
#endif
    clipRect.X_Top_Left = 0;
    clipRect.Y_Top_Left = 0;
    clipRect.X_Bottom_Right = info->src.w;
    clipRect.Y_Bottom_Right = info->src.h;
    ret = AtiCore_SetDstClippingRect(&clipRect);
    clipRect.X_Bottom_Right = info->src.w;
    clipRect.Y_Bottom_Right = info->src.h;
    ret = AtiCore_SetSrcClippingRect(&clipRect);

    AtiCore_SetOverlayPos(g_overlayHandle, (info->dest.x < 4)?4:info->dest.x, info->dest.y);

    AtiCore_SetRopOperation(ROP3_SRCCOPY);
    AtiCore_SetDstType(DSTTYPE_8BPP);
    AtiCore_SetSrcType(SRCTYPE_EQU_DST);

    vixPlaybackSetEq(&st_equal);

    memcpy(&st_playbackInfo, info, sizeof(*info));
#ifdef DEBUG
    fprintf(stderr, "w100_vid: ---- vixConfigPlayback complete.\n");
#endif
    return 0;
}

int vixPlaybackOn(void)
{
    AtiCore_SetOverlayOnOff(g_overlayHandle, 1);

    return 0;
}

int vixPlaybackOff(void)
{
    AtiCore_SetOverlayOnOff(g_overlayHandle, 0);

    return 0;
}

int vixPlaybackFrameSelect(unsigned int frame)
{
    ATI_STRETCH stretchOptions;
    ATI_POINT dpPoint;
    ATI_RECT srcRect;
    int ret;
    int pitch_y, pitch_uv;

    if (frame != 1) return 0;

    stretchOptions.Count = 1;
    stretchOptions.ScaleXFactor = 16;
    stretchOptions.ScaleYFactor = 16;
    stretchOptions.BlendOn = 0;
    stretchOptions.dummy1 = 0;

    dpPoint.XCoord = 0;
    dpPoint.YCoord = 0;

    srcRect.XCoord = st_playbackInfo.src.x;
    srcRect.YCoord = st_playbackInfo.src.y;
    srcRect.Width = st_playbackInfo.src.w;
    srcRect.Height = st_playbackInfo.src.h;

    while (AtiCore_WaitComplete(100) != 1)
        ;

    pitch_y = (st_playbackInfo.src.w + 15) & ~15;

    ret = AtiCore_SetSrcPitchOffset(pitch_y, VRAMoffset2);
    ret = AtiCore_SetDstPitchOffset(pitch_y, VRAMoffset );
    ret = AtiCore_StretchBlt(&stretchOptions, &dpPoint, &srcRect);

    srcRect.Width >>=1;
    srcRect.Height >>= 1;
    pitch_uv = ((st_playbackInfo.src.w / 2) + 7) & ~7;

    ret = AtiCore_SetSrcPitchOffset(pitch_uv, VRAMoffset2 + st_playbackInfo.offset.u);
    ret = AtiCore_SetDstPitchOffset(pitch_uv, VRAMoffset  + st_playbackInfo.offset.u);
    ret = AtiCore_StretchBlt(&stretchOptions, &dpPoint, &srcRect);

    ret = AtiCore_SetSrcPitchOffset(pitch_uv, VRAMoffset2 + st_playbackInfo.offset.v);
    ret = AtiCore_SetDstPitchOffset(pitch_uv, VRAMoffset  + st_playbackInfo.offset.v);
    ret = AtiCore_StretchBlt(&stretchOptions, &dpPoint, &srcRect);

    return 0;
}
