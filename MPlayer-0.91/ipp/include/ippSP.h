/******************************************************************************
//               INTEL CORPORATION PROPRIETARY INFORMATION
//	This software is supplied under the terms of a license agreement or
//	nondisclosure agreement with Intel Corporation and may not be copied
//	or disclosed except in accordance with the terms of that agreement.
//	     Copyright (c) 1999-2001 Intel Corporation. All Rights Reserved.
//
//	Description:
//          Intel(R) Integrated Performance Primitives - Signal Processing
//                             Version 1.11
//
******************************************************************************/

#ifndef _IPPSP_H_
#define _IPPSP_H_

#include "ippdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IPP_MAX_EXP 308

/* =============== Structure Definition for Sample Generation ============== */

typedef struct {
	Ipp32s	cosBase;
	Ipp32s	sinBase;
	Ipp32s	cosCurr;
	Ipp32s	sinCurr;
} IppToneState_16s;

typedef struct {
    Ipp64s	mag;
    Ipp64s	step;
    Ipp64s	step1;
    Ipp64s	step2;
    Ipp64s	st12;
    Ipp64s	st21;
    Ipp64s	last;
 } IppTriangleState_16s;

typedef struct {
	Ipp32s  high; 
	Ipp32s	low;
	Ipp32s	m_seed[2];                       
	Ipp32s	d_seed[3];                       
	Ipp32s	carry;
	Ipp32s  quickSeed;
	Ipp32s  current;
} IppRandUniformState_16s;

typedef struct {
	Ipp32s   useExtra;
	Ipp32s	seed2;
	Ipp32s	carry;
	Ipp32s	seed1[3];
	Ipp16s   mean;
	Ipp16s	stdDev;
	Ipp16s   extraValue;
	Ipp32s   quickSeed;
} IppRandGaussState_16s;


/* =============== Structure Definition for 2^N variant length FFT ============== */

typedef struct {
	int	tableLen;
	Ipp16s *cosTable;
	Ipp16s *sinTable;
} IPPFFTRecombTables;

typedef struct{
	int	tableLen;
	Ipp16s *cosTable1;
	Ipp16s *sinTable1;
	Ipp16s *cosTable2;
	Ipp16s *sinTable2;
} IPPFFTTrnsTables;

/* =============== Structure Definition for 2^N variant length MDCT ============== */

typedef struct{
	int	tableLen1;
	Ipp16s *cosTable; 
	Ipp16s *sinTable; 
	int	tableLen2;
	Ipp16s *cosTable1;
	Ipp16s *sinTable1;
	Ipp16s *cosTable2;
	Ipp16s *sinTable2;
} IPPMDCTTables;

/* =========================== General Functions =========================== */


/* Addition */
IPPAPI(IppStatus, ippsAddC_16s_I,
	(Ipp16s val, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsAddC_16s_ISfs,	
	(Ipp16s val, Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsAddC_16s,	
	(Ipp16s val, const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsAddC_16s_Sfs,	
	(Ipp16s val, const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsAdd_16s_I,	
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsAdd_16s_ISfs,	
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len , int scaleFactor))

IPPAPI(IppStatus, ippsAdd_16s,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsAdd_16s_Sfs,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, Ipp16s * pDst, int len, 
	int scaleFactor))

/* Subtraction */	   
IPPAPI(IppStatus, ippsSubC_16s_I,
	(Ipp16s val, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsSubC_16s_ISfs,
	(Ipp16s val, Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsSubC_16s,	
	(Ipp16s val, const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsSubC_16s_Sfs,	
	(Ipp16s val, const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsSub_16s_I,
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsSub_16s_ISfs,	
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsSub_16s,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsSub_16s_Sfs,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, Ipp16s * pDst, int len, 
	int scaleFactor))

IPPAPI(IppStatus, ippsSubInvC_16s_I,	
	(Ipp16s val, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsSubInvC_16s_ISfs,	
	(Ipp16s val, Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsSubInv_16s_I,	
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsSubInv_16s_ISfs,	
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len, int scaleFactor))


/* Multiplication */	   
IPPAPI(IppStatus, ippsMulC_16s_I,
	(Ipp16s val, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsMulC_16s_ISfs,
	(Ipp16s val, Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsMulC_16s,	
	(Ipp16s val, const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsMulC_16s_Sfs,	
	(Ipp16s val, const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsMul_16s_I,
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsMul_16s_ISfs,	
	(const Ipp16s * pSrc, Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsMul_16s,
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsMul_16s_Sfs,
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, Ipp16s * pDst, int len, 
	int scaleFactor))


/* Absolution */	
IPPAPI(IppStatus, ippsAbs_16s_I,
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsAbs_16s,
	(const Ipp16s * pSrc, Ipp16s * pDst, int len))

/* Square */
IPPAPI(IppStatus, ippsSqr_16s_I,	
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsSqr_16s_ISfs,	
	(Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsSqr_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsSqr_16s_Sfs,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))

/* Square root */
IPPAPI(IppStatus, ippsSqrt_16s_I,
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsSqrt_16s_ISfs,
	(Ipp16s * pSrcDst, int len , int scaleFactor))

IPPAPI(IppStatus, ippsSqrt_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsSqrt_16s_Sfs,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))

/* Exponent */
IPPAPI(IppStatus, ippsExp_16s_I,
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsExp_16s_ISfs,	
	(Ipp16s * pSrcDst, int len, int scaleFactor))

IPPAPI(IppStatus, ippsExp_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsExp_16s_Sfs,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))


/* Logarithm */
IPPAPI(IppStatus, ippsLn_16s_I,	
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsLn_16s_ISfs,	
	(Ipp16s * pSrcDst, int len , int scaleFactor))

IPPAPI(IppStatus, ippsLn_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len))

IPPAPI(IppStatus, ippsLn_16s_Sfs,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, int scaleFactor))

	
/* Dot product */
IPPAPI(IppStatus, ippsDotProd_16s,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp16s * pResult))

IPPAPI(IppStatus, ippsDotProd_16s_Sfs,
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp16s * pResult, 
	int scaleFactor))

/* Threshold */
IPPAPI(IppStatus, ippsThreshold_GT_16s_I,	
	(Ipp16s * pSrcDst, int len, Ipp16s threshold))

IPPAPI(IppStatus, ippsThreshold_GT_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s threshold))

IPPAPI(IppStatus, ippsThreshold_GTVal_16s_I,	
	(Ipp16s * pSrcDst, int len, Ipp16s threshold, Ipp16s val))

IPPAPI(IppStatus, ippsThreshold_GTVal_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s threshold, Ipp16s val))

IPPAPI(IppStatus, ippsThreshold_LT_16s_I,
	(Ipp16s * pSrcDst, int len, Ipp16s threshold))

IPPAPI(IppStatus, ippsThreshold_LT_16s,
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s threshold))

IPPAPI(IppStatus, ippsThreshold_LTVal_16s_I,
	(Ipp16s * pSrcDst, int len, Ipp16s threshold, Ipp16s val))

IPPAPI(IppStatus, ippsThreshold_LTVal_16s,
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s threshold, Ipp16s val))

IPPAPI(IppStatus, ippsThreshold_GTValLTVal_16s_I,
	(Ipp16s * pSrcDst, int len, Ipp16s gtThreshold, Ipp16s gtVal, 
	Ipp16s ltThreshold, Ipp16s ltVal))

IPPAPI(IppStatus, ippsThreshold_GTValLTVal_16s,
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s gtThreshold, Ipp16s gtVal, 
	Ipp16s ltThreshold, Ipp16s ltVal))

/* Normalization */
IPPAPI(IppStatus, ippsNormalize_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s offset, int normFactor))

IPPAPI(IppStatus, ippsNormalize_16s_Sfs,
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, Ipp16s offset, int normFactor, 
	int scaleFactor))

/* Copy */
IPPAPI(IppStatus, ippsCopy_16s,
	(const Ipp16s * pSrc, Ipp16s * pDst, int len))

/* Set */
IPPAPI(IppStatus, ippsSet_16s,
	(Ipp16s val, Ipp16s * pDst, int len))

/* Zero */
IPPAPI(IppStatus, ippsZero_16s,
	(Ipp16s * pDst, int len))

/* Max */
IPPAPI(IppStatus, ippsMax_16s,
	(const Ipp16s * pSrc, int len, Ipp16s * pResult))

/* Min */
IPPAPI(IppStatus, ippsMin_16s,
	(const Ipp16s * pSrc, int len, Ipp16s * pResult))

/* Mean	*/
IPPAPI(IppStatus, ippsMean_16s,
	(const Ipp16s * pSrc, int len, Ipp16s * pResult))

/* Standard deviation */
IPPAPI(IppStatus, ippsStdDev_16s,	
	(const Ipp16s * pSrc, int len, Ipp16s * pResult))

IPPAPI(IppStatus, ippsStdDev_16s_Sfs,	
	(const Ipp16s * pSrc, int len, Ipp16s * pResult, int scaleFactor))

/* Norm	*/
IPPAPI(IppStatus, ippsNormDiff_L1_16s32s,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp32s * pResult))

IPPAPI(IppStatus, ippsNormDiff_L1_16s32s_Sfs,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp32s * pResult,
	int scaleFactor))

IPPAPI(IppStatus, ippsNormDiff_L2_16s32s,
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp32s * pResult))

IPPAPI(IppStatus, ippsNormDiff_L2_16s32s_Sfs,
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp32s * pResult, 
	int scaleFactor))

IPPAPI(IppStatus, ippsNormDiff_Inf_16s32s,
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp32s * pResult))

IPPAPI(IppStatus, ippsNormDiff_Inf_16s32s_Sfs,	
	(const Ipp16s * pSrc1, const Ipp16s * pSrc2, int len, Ipp32s * pResult, 
	int scaleFactor))

IPPAPI(IppStatus, ippsNorm_L1_16s32s,
	(const Ipp16s * pSrc, int len, Ipp32s * pResult))

IPPAPI(IppStatus, ippsNorm_L1_16s32s_Sfs,	
	(const Ipp16s * pSrc, int len, Ipp32s * pResult, int scaleFactor))

IPPAPI(IppStatus, ippsNorm_L2_16s32s,
	(const Ipp16s * pSrc, int len, Ipp32s * pResult))

IPPAPI(IppStatus, ippsNorm_L2_16s32s_Sfs,
	(const Ipp16s * pSrc, int len, Ipp32s * pResult, int scaleFactor))

IPPAPI(IppStatus, ippsNorm_Inf_16s32s,	
	(const Ipp16s * pSrc, int len, Ipp32s * pResult))

IPPAPI(IppStatus, ippsNorm_Inf_16s32s_Sfs,
	(const Ipp16s * pSrc, int len, Ipp32s * pResult, int scaleFactor))

/* Upsample */
IPPAPI(IppStatus, ippsUpSample_16s,	
	(const Ipp16s * pSrc, int srcLen, int * pSrcDstPhase, Ipp16s * pDst, 
	int sampleFactor))

IPPAPI(IppStatus, ippsUpSampleSize,	
	(int srcLen, int sampleFactor, int phase, int * pDstLen))

/* Downsample */
IPPAPI(IppStatus, ippsDownSample_16s,
	(const Ipp16s * pSrc, int srcLen, int * pSrcDstPhase, Ipp16s * pDst, 
	int sampleFactor))

IPPAPI(IppStatus, ippsDownSampleSize,
	(int srcLen, int sampleFactor, int phase, int * pDstLen))

/* Correlation */
IPPAPI(IppStatus, ippsAutoCorr_16s,	
	(const Ipp16s * pSrc, int srcLen, Ipp16s * pDst, int dstLen))

IPPAPI(IppStatus, ippsAutoCorr_16s_Sfs,	
	(const Ipp16s * pSrc, int srcLen, Ipp16s * pDst, int dstLen, 
	int scaleFactor))

IPPAPI(IppStatus, ippsAutoCorr_NormA_16s,
	(const Ipp16s * pSrc, int srcLen, Ipp16s * pDst, int dstLen))

IPPAPI(IppStatus, ippsAutoCorr_NormA_16s_Sfs,
	(const Ipp16s * pSrc, int srcLen, Ipp16s * pDst, int dstLen, 
	int scaleFactor))

IPPAPI(IppStatus, ippsAutoCorr_NormB_16s,
	(const Ipp16s * pSrc, int srcLen, Ipp16s * pDst, int dstLen))

IPPAPI(IppStatus, ippsAutoCorr_NormB_16s_Sfs,
	(const Ipp16s * pSrc, int srcLen, Ipp16s * pDst, int dstLen, 
	int scaleFactor))

IPPAPI(IppStatus, ippsCrossCorr_16s,
	(const Ipp16s * pSrc1, int src1Len, const Ipp16s * pSrc2, int src2Len,
	Ipp16s * pDst, int dstLen, int lowLag))

IPPAPI(IppStatus, ippsCrossCorr_16s_Sfs,
	(const Ipp16s * pSrc1, int src1Len, const Ipp16s * pSrc2, int src2Len,
	Ipp16s * pDst, int dstLen, int lowLag, int scaleFactor))

/* =========================== Filter Functions ============================ */
	
/* FIR single rate */
IPPAPI(IppStatus, ippsFIR_Direct_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int sampLen, const Ipp16s * pTapsQ15, 
	int tapsLen, Ipp16s * pDelayLine, int * pDelayLineIndex))

IPPAPI(IppStatus, ippsFIR_Direct_16s_I,	
	(Ipp16s * pSrcDst, int sampLen, const Ipp16s * pTapsQ15, int tapsLen, 
	Ipp16s * pDelayLine, int * pDelayLineIndex))

IPPAPI(IppStatus, ippsFIROne_Direct_16s,
	(Ipp16s val, Ipp16s * pResult, const Ipp16s * pTapsQ15, int tapsLen, 
	Ipp16s * pDelayLine, int * pDelayLineIndex))

IPPAPI(IppStatus, ippsFIROne_Direct_16s_I,	
	(Ipp16s * pValResult, const Ipp16s * pTapsQ15, int tapsLen, 
	Ipp16s * pDelayLine, int * pDelayLineIndex))


IPPAPI(IppStatus, ippsFIR_Direct_16s_Sfs,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int sampLen, const Ipp16s * pTapsQ15, 
	int tapsLen, Ipp16s * pDelayLine, int * pDelayLineIndex, int scaleFactor))

IPPAPI(IppStatus, ippsFIR_Direct_16s_ISfs,	
	(Ipp16s * pSrcDst, int sampLen, const Ipp16s * pTapsQ15, int tapsLen, 
	Ipp16s * pDelayLine, int * pDelayLineIndex, int scaleFactor))

IPPAPI(IppStatus, ippsFIROne_Direct_16s_Sfs,
	(Ipp16s val, Ipp16s * pResult, const Ipp16s * pTapsQ15, int tapsLen, 
	Ipp16s * pDelayLine, int * pDelayLineIndex, int scaleFactor))

IPPAPI(IppStatus, ippsFIROne_Direct_16s_ISfs,	
	(Ipp16s * pValResult, const Ipp16s * pTapsQ15, int tapsLen, 
	Ipp16s * pDelayLine, int * pDelayLineIndex, int scaleFactor))


/* IIR direct form */
IPPAPI(IppStatus, ippsIIR_Direct_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, const Ipp16s * pTaps, 
	int order, Ipp32s * pDelayLine))

IPPAPI(IppStatus, ippsIIR_Direct_16s_I,	
	(Ipp16s * pSrcDst, int len, const Ipp16s * pTaps, int order, 
	Ipp32s * pDelayLine))

IPPAPI(IppStatus, ippsIIROne_Direct_16s,
	(Ipp16s val, Ipp16s * pResult, const Ipp16s * pTaps, int order, 
	Ipp32s * pDelayLine))

IPPAPI(IppStatus, ippsIIROne_Direct_16s_I,
	(Ipp16s * pValResult, const Ipp16s * pTaps, int order, Ipp32s * pDelayLine))

/* IIR biquad */
IPPAPI(IppStatus, ippsIIR_BiQuadDirect_16s,	
	(const Ipp16s * pSrc, Ipp16s * pDst, int len, const Ipp16s * pTaps, 
	int numBiquad, Ipp32s * pDelayLine))

IPPAPI(IppStatus, ippsIIR_BiQuadDirect_16s_I,
	(Ipp16s * pSrcDst, int len, const Ipp16s * pTaps, int numBiquad, 
	Ipp32s * pDelayLine))

IPPAPI(IppStatus, ippsIIROne_BiQuadDirect_16s,
	(Ipp16s val, Ipp16s * pResult, const Ipp16s * pTaps, int numBiquad, 
	Ipp32s * pDelayLine))

IPPAPI(IppStatus, ippsIIROne_BiQuadDirect_16s_I,
	(Ipp16s * pValResult, const Ipp16s * pTaps, int numBiquad, 
	Ipp32s * pDelayLine))

/* LMS FIR */
IPPAPI(IppStatus, ippsFIRLMSOne_Direct_16s,	
	(Ipp16s val, Ipp16s valDesire, Ipp16s * pResult, Ipp32s * pTapsQ15, 
	int tapsLen, Ipp32s stepQ15, Ipp16s * pDelayLine, int * pDelayLineIndex))

IPPAPI(IppStatus, ippsFIRLMSOne_Direct_16s_I,	
	(Ipp16s * pValResult, Ipp16s valDesire, Ipp32s * pTapsQ15, int tapsLen, 
	Ipp32s stepQ15, Ipp16s * pDelayLine, int * pDelayLineIndex))
		
/* ========================= Convolution Functions ========================= */

/* 1D convolution */
IPPAPI(IppStatus, ippsConv_16s,	
	(const Ipp16s * pSrc1, int src1Len, const Ipp16s * pSrc2, int src2Len, 
	Ipp16s * pDst))

IPPAPI(IppStatus, ippsConv_16s_Sfs,	
	(const Ipp16s * pSrc1, int src1Len, const Ipp16s * pSrc2, int src2Len,
	Ipp16s * pDst, int scaleFactor))

IPPAPI(IppStatus, ippsConvSize,	
	(int src1Len, int src2Len, int * pDstLen))

/* 1D convolution */
IPPAPI(IppStatus, ippsConv_16s_D2,	
	(const Ipp16s * pSrc1, int src1HSize, int src1VSize, const Ipp16s * pSrc2,
	int src2HSize, int src2VSize, Ipp16s * pDst))

IPPAPI(IppStatus, ippsConv_16s_D2Sfs,
	(const Ipp16s * pSrc1, int src1HSize, int src1VSize, const Ipp16s * pSrc2,
	int src2HSize, int src2VSize, Ipp16s * pDst, int scaleFactor))

IPPAPI(IppStatus, ippsConvSize_D2,	
	(int src1HSize, int src1VSize, int src2HSize, int src2VSize, 
	int * pDstHSize, int * pDstVSize))
		
/* ========================== Transform Functions ========================== */

/* Fixed length FFT */
IPPAPI(IppStatus, ippsFFTFwd_RToCCSL128_16s32sc,
	(const Ipp16s * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_RToCCSL256_16s32sc,
	(const Ipp16s * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_RToCCSL512_16s32sc,
	(const Ipp16s * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_RToCCSL1024_16s32sc,
	(const Ipp16s * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CCSToRL128_32sc32s,
	(const Ipp32sc * pSrc, Ipp32s * pDst))

IPPAPI(IppStatus, ippsFFTInv_CCSToRL256_32sc32s,
	(const Ipp32sc * pSrc, Ipp32s * pDst))

IPPAPI(IppStatus, ippsFFTInv_CCSToRL512_32sc32s,
	(const Ipp32sc * pSrc, Ipp32s * pDst))

IPPAPI(IppStatus, ippsFFTInv_CCSToRL1024_32sc32s,
	(const Ipp32sc * pSrc, Ipp32s * pDst))

/* Fixed length complex FFT */

IPPAPI(IppStatus, ippsFFTFwd_CToCL32_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_CToCL64_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_CToCL128_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_CToCL256_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_CToCL512_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTFwd_CToCL1024_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CToCL32_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CToCL64_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CToCL128_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CToCL256_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CToCL512_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

IPPAPI(IppStatus, ippsFFTInv_CToCL1024_32sc,
	(const Ipp32sc * pSrc, Ipp32sc * pDst))

/* ========================== Windowing Functions ========================== */

IPPAPI(IppStatus, ippsWinBartlett_16s_I,
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsWinHann_16s_I,
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsWinHamming_16s_I,	
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsWinBlackmanQ15_16s_I,
	(Ipp16s * pSrcDst, int len, Ipp32s alphaQ15))

IPPAPI(IppStatus, ippsWinBlackmanQ15_16s_ISfs,	
	(Ipp16s * pSrcDst, int len, Ipp32s alphaQ15, int scaleFactor))

IPPAPI(IppStatus, ippsWinBlackmanStd_16s_I,	
	(Ipp16s * pSrcDst, int len))

IPPAPI(IppStatus, ippsWinBlackmanOpt_16s_I,	
	(Ipp16s * pSrcDst, int len))


/* ====================== Sample Generation Functions ====================== */

/* Tone */
IPPAPI(IppStatus, ippsToneGetSizeQ15_16s,
	(int * pToneStateSize))

IPPAPI(IppStatus, ippsToneInitQ15_16s,	
	(IppToneState_16s * pToneState, Ipp16s magQ15, Ipp16s freqQ15, 
	Ipp32s phaseQ15))

IPPAPI(IppStatus, ippsToneQ15_16s,	
	(Ipp16s * pDst, int len, IppToneState_16s * pToneState))

IPPAPI(IppStatus, ippsToneQ15_Direct_16s,
	(Ipp16s * pDst, int len, Ipp16s magQ15, Ipp16s freqQ15, Ipp32s phaseQ15))

/* Triangle */
IPPAPI(IppStatus, ippsTriangleGetSizeQ15_16s,
	(int * pTriangleStateSize))

IPPAPI(IppStatus, ippsTriangleInitQ15_16s,
	(IppTriangleState_16s * pTriangleState, Ipp16s MagQ15, Ipp16s freqQ15, 
	Ipp32s phaseQ15, Ipp32s asymQ15))

IPPAPI(IppStatus, ippsTriangleQ15_16s,	
	(Ipp16s * pDst, int len, IppTriangleState_16s * pTriangleState))

IPPAPI(IppStatus, ippsTriangleQ15_Direct_16s,	
	(Ipp16s * pDst, int len, Ipp16s magQ15, Ipp16s freqQ15, Ipp32s phaseQ15, 
	Ipp32s asymQ15))

/* Random */
IPPAPI(IppStatus, ippsRandUniformGetSize_16s,
	(int * pRandUniformStateSize))

IPPAPI(IppStatus, ippsRandUniformInit_16s,
	(IppRandUniformState_16s * pRandUniformState, 
	Ipp16s low, Ipp16s high, Ipp16s seed))

IPPAPI(IppStatus, ippsRandUniform_16s,
	(Ipp16s * pDst, int len, IppRandUniformState_16s * pRandUniformState))

IPPAPI(IppStatus, ippsRandGaussGetSize_16s,	
	(int * pRandGaussStateSize))

IPPAPI(IppStatus, ippsRandGaussInit_16s,
	(IppRandGaussState_16s * pRandGaussState, Ipp16s mean, 
	Ipp16s stdDev, Ipp32u seed))

IPPAPI(IppStatus, ippsRandGauss_16s,
	(Ipp16s * pDst, int len, IppRandGaussState_16s * pRandGaussState))

#ifdef __cplusplus
}
#endif

#endif /* _IPPSP_H_ */ 
	
/* End of file */
