/********************************************************************************
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 2000 Intel Corporation. All Rights Reserved.
//
//  Description:
//      Intel(R) Integrated Performance Primitives - Video Processing header file.
//                             Version 1.11
//
//      This file contains declarations specific to the video coding domain.
********************************************************************************/

#ifndef _IPPVC_H_
#define _IPPVC_H_

#include "ippdefs.h"

#ifdef __cplusplus
extern "C" {
#endif


/***** Data Types, Data Structures and Constants ********************************/

/* Video Components */
typedef enum {
	IPP_VIDEO_LUMINANCE,		/* Luminance component   */
	IPP_VIDEO_CHROMINANCE,		/* Chrominance component */
	IPP_VIDEO_ALPHA				/* Alpha component       */
} IppVideoComponent;

/* Macroblock Types */
typedef enum {
	IPP_VIDEO_INTER			= 0,	/* P picture or P-VOP */
	IPP_VIDEO_INTER_Q		= 1,	/* P picture or P-VOP */
	IPP_VIDEO_INTER4V		= 2,	/* P picture or P-VOP */
	IPP_VIDEO_INTRA			= 3,	/* I and P picture, or I- and P-VOP */
	IPP_VIDEO_INTRA_Q		= 4,	/* I and P picture, or I- and P-VOP */
	IPP_VIDEO_INTER4V_Q		= 5,	/* P picture or P-VOP(H.263)*/
	IPP_VIDEO_DIRECT		= 6,	/* B picture or B-VOP (MPEG-4 only) */
	IPP_VIDEO_INTERPOLATE	= 7,	/* B picture or B-VOP */
	IPP_VIDEO_BACKWARD		= 8,	/* B picture or B-VOP */
	IPP_VIDEO_FORWARD		= 9		/* B picture or B-VOP */
} IppMacroblockType;

/* Motion Vector */
typedef struct _IppMotionVector {
	Ipp16s	dx;
	Ipp16s	dy;
} IppMotionVector;

/* Transparent Status */
enum {
	IPP_VIDEO_TRANSPARENT	= 0,
	IPP_VIDEO_PARTIAL		= 1,
	IPP_VIDEO_OPAQUE		= 2
};

/* Direction */
enum {
	IPP_VIDEO_NONE			= 0,
	IPP_VIDEO_HORIZONTAL	= 1,
	IPP_VIDEO_VERTICAL		= 2,
	IPP_VIDEO_DCONLY		= 3
};

enum {IPP_DCScalerLinear, IPP_DCScalerNonLinear};

/***** Video Coding Functions **************************************************/


/***** General Video Functions *****/

/* 8 by 8 Inverse Discrete Cosine Transform */
IPPAPI(IppStatus, ippiDCTInv_8x8_16s, (const Ipp16s * pSrc, Ipp16s * pDst))

IPPAPI(IppStatus, ippiDCTInv_8x8_16s_I, (Ipp16s * pSrcDst))

IPPAPI(IppStatus, ippiDCTInv_8x8_16s8u, (const Ipp16s * pSrc, Ipp8u * pDst, int dstStep))

/* Inverse Zigzag Scanning */

IPPAPI(IppStatus, ippiZigzagInvClassical_Compact_16s,
	(const Ipp16s * pSrc, int len, Ipp16s * pDst))

IPPAPI(IppStatus, ippiZigzagInvHorizontal_Compact_16s,
	(const Ipp16s * pSrc, int len, Ipp16s * pDst))

IPPAPI(IppStatus, ippiZigzagInvVertical_Compact_16s,
	(const Ipp16s * pSrc, int len, Ipp16s * pDst))

/* Prediction with Overlapped Block Motion Compensation (OBMC) */
IPPAPI(IppStatus, ippiPredictBlock_OBMC_8u,
	(const Ipp8u * pSrcRef, Ipp8u * pDst, int step,
	 IppMotionVector * pMVCur, IppMotionVector * pMVLeft, IppMotionVector * pMVRight,
	 IppMotionVector * pMVAbove, IppMotionVector * pMVBelow))

/***** H.263+ Functions *****/

IPPAPI(IppStatus, ippiDecodeMV_H263,
	(Ipp8u ** ppBitStream, int * pBitOffset, IppMotionVector * pSrcDstMV))

IPPAPI(IppStatus, ippiDecodeMV_TopBorder_H263,
	(Ipp8u ** ppBitStream, int * pBitOffset, IppMotionVector * pSrcDstMV))

/* Copy */
IPPAPI(IppStatus, ippiCopyMB_H263_8u,
	(const Ipp8u * pSrc, Ipp8u * pDst, int step))

IPPAPI(IppStatus, ippiCopyBlock_H263_8u,
	(const Ipp8u * pSrc, Ipp8u * pDst, int step))

/* Quantization */
IPPAPI(IppStatus, ippiQuantInvIntra_Compact_H263_16s_I,
	(Ipp16s * pSrcDst, int len, int QP))

IPPAPI(IppStatus, ippiQuantInvInter_Compact_H263_16s_I,
	(Ipp16s * pSrcDst, int len, int QP))

/* Reconstruction */
IPPAPI(IppStatus, ippiReconMB_H263,
	(const Ipp8u * pSrc, const Ipp16s * pSrcResidual, Ipp8u * pDst, int step))

IPPAPI(IppStatus, ippiReconMB_H263_I,
	(Ipp8u * pSrcDst, const Ipp16s * pSrcResidual, int step))

IPPAPI(IppStatus, ippiReconBlock_H263,
	(const Ipp8u * pSrc, const Ipp16s * pSrcResidual, Ipp8u * pDst, int step))

IPPAPI(IppStatus, ippiReconBlock_H263_I,
	(Ipp8u * pSrcDst, const Ipp16s * pSrcResidual, int step))

/* Expand Frame */
IPPAPI(IppStatus, ippiExpandFrame_H263_8u,
	(Ipp8u * pSrcDstPlane, int frameWidth, int frameHeight, int expandPels, int step))

/* Deblock Filtering */
IPPAPI(IppStatus, ippiFilterDeblocking_HorEdge_H263_8u_I,
	(Ipp8u * pSrcDst, int step, int QP))

IPPAPI(IppStatus, ippiFilterDeblocking_VerEdge_H263_8u_I,
	(Ipp8u * pSrcDst, int step, int QP))


/* Middle Level */
IPPAPI(IppStatus, ippiDecodeBlockCoef_Intra_H263_1u8u,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp8u * pDst, int step, int QP))

IPPAPI(IppStatus, ippiDecodeBlockCoef_Inter_H263_1u16s,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp16s * pDst, int QP))


/***** MPEG-4 Functions *****/

/* motion vector decoding (+ padding) */
IPPAPI(IppStatus, ippiDecodePadMV_PVOP_MPEG4,
	(Ipp8u ** ppBitStream, int * pBitOffset,
	 IppMotionVector * pSrcMVLeftMB, IppMotionVector * pSrcMVUpperMB, 
	 IppMotionVector * pSrcMVUpperRightMB, IppMotionVector * pDstMVCurMB,
	 Ipp8u * pTranspLeftMB, Ipp8u * pTranspUpperMB, Ipp8u * pTranspUpperRightMB, 
	 Ipp8u * pTranspCurMB, int fcodeForward, IppMacroblockType MBType))

IPPAPI(IppStatus, ippiDecodeMV_BVOP_Forward_MPEG4,
	(Ipp8u ** ppBitStream, int * pBitOffset,
	 IppMotionVector * pSrcDstMVF,int fcodeForward))

IPPAPI(IppStatus, ippiDecodeMV_BVOP_Backward_MPEG4,
	(Ipp8u ** ppBitStream, int * pBitOffset,
	 IppMotionVector * pSrcDstMVB,int fcodeBackward))

IPPAPI(IppStatus, ippiDecodeMV_BVOP_Interpolate_MPEG4,
	(Ipp8u ** ppBitStream, int * pBitOffset,
	 IppMotionVector * pSrcDstMVF, IppMotionVector * pSrcDstMVB,
	 int fcodeForward, int fcodeBackward))

IPPAPI(IppStatus, ippiDecodeMV_BVOP_Direct_MPEG4,
	(Ipp8u ** ppBitStream, int * pBitOffset,
	 const IppMotionVector * pSrcMV, IppMotionVector * pDstMVF, IppMotionVector * pDstMVB,
	 Ipp8u * pTranspSrcMB, int TRB, int TRD))

IPPAPI(IppStatus, ippiDecodeMV_BVOP_DirectSkip_MPEG4,
	(const IppMotionVector * pSrcMV, IppMotionVector * pDstMVF, IppMotionVector * pDstMVB,
	 Ipp8u * pTranspSrcMB, int TRB, int TRD))


IPPAPI(IppStatus,ippiLimitMVToRect_MPEG4,
	 (const IppMotionVector * pSrcMV,IppMotionVector *pDstMV,IppiRect *pRectVOPRef, int x,
	  int y,int size))

/* coefficient prediction + reconstruction */
IPPAPI(IppStatus, ippiPredictReconCoefIntra_MPEG4_16s,
	(Ipp16s * pSrcDst, Ipp16s * pPredBufRow, Ipp16s * pPredBufCol,
	 int curQP, int predQP, int predDir, int ACPredFlag, IppVideoComponent videoComp))

/* motion padding */
IPPAPI(IppStatus, ippiPadMBHorizontal_MPEG4_8u,
	(const Ipp8u * pSrcY, const Ipp8u * pSrcCb, 
	 const Ipp8u * pSrcCr, const Ipp8u * pSrcA, 
	 Ipp8u * pDstY, Ipp8u * pDstCb, Ipp8u * pDstCr, Ipp8u * pDstA, int stepYA, int stepCbCr))

IPPAPI(IppStatus, ippiPadMBVertical_MPEG4_8u, 
	   (const Ipp8u * pSrcY, const Ipp8u * pSrcCb, 
	    const Ipp8u * pSrcCr, const Ipp8u * pSrcA,
		Ipp8u * pDstY, Ipp8u * pDstCb, Ipp8u * pDstCr, Ipp8u * pDstA, int stepYA, int stepCbCr))

IPPAPI(IppStatus, ippiPadMBGray_MPEG4_8u, (Ipp8u grayVal, Ipp8u * pDstY, 
	   Ipp8u * pDstCb, Ipp8u * pDstCr, Ipp8u * pDstA, int stepYA, int stepCbCr))

IPPAPI(IppStatus, ippiPadCurrent_16x16_MPEG4_8u_I,
	(const Ipp8u * pSrcBAB, int stepBinary, Ipp8u * pSrcDst, int stepTexture))

IPPAPI(IppStatus, ippiPadCurrent_8x8_MPEG4_8u_I,
	(const Ipp8u * pSrcBAB, int stepTexture, Ipp8u * pSrcDst))


/* vector padding */
IPPAPI(IppStatus, ippiPadMV_MPEG4,
	(IppMotionVector * pSrcDstMV, Ipp8u * pTransp))

/* inverse quantization */

IPPAPI(IppStatus, ippiQuantInvIntra_MPEG4_16s_I,
	(Ipp16s * pSrcDst, int QP, const Ipp8u * pQMatrix, IppVideoComponent videoComp))

IPPAPI(IppStatus, ippiQuantInvInter_MPEG4_16s_I,
	(Ipp16s * pSrcDst, int QP, const Ipp8u * pQMatrix))

/* vlc decoding + zigzag */
IPPAPI(IppStatus, ippiDecodeVLCZigzag_IntraDCVLC_MPEG4_1u16s,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp16s * pDst, int predDir, IppVideoComponent videoComp))

IPPAPI(IppStatus, ippiDecodeVLCZigzag_IntraACVLC_MPEG4_1u16s,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp16s * pDst, int predDir))

IPPAPI(IppStatus, ippiDecodeVLCZigzag_Inter_MPEG4_1u16s,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp16s * pDst))

/* block decoding */
IPPAPI(IppStatus, ippiDecodeBlockCoef_Intra_MPEG4_1u8u,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp8u * pDst,
	 int step, Ipp16s * pCoefBufRow, Ipp16s * pCoefBufCol,
	 Ipp8u curQP, Ipp8u * pQPBuf, const Ipp8u * pQMatrix,
	 int blockIndex, int intraDCVLC, int ACPredFlag))

IPPAPI(IppStatus, ippiDecodeBlockCoef_Inter_MPEG4_1u16s,
	(Ipp8u ** ppBitStream, int * pBitOffset, Ipp16s * pDst,
	 int QP, const Ipp8u * pQMatrix))



#ifdef __cplusplus
}
#endif

#endif	/* #ifndef _IPPVC_H_ */

/* EOF */

