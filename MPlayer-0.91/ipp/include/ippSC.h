/******************************************************************************
//               INTEL CORPORATION PROPRIETARY INFORMATION
//	This software is supplied under the terms of a license agreement or
//	nondisclosure agreement with Intel Corporation and may not be copied
//	or disclosed except in accordance with the terms of that agreement.
//	     Copyright (c) 2001 Intel Corporation. All Rights Reserved.
//
//  Description:
//      Intel(R) Integrated Performance Primitives - Speech Processing header file.
//                             Version 1.11
//
//      This file contains declarations specific to the speech coding domain.
******************************************************************************/

#ifndef _IPPSC_H_
#define _IPPSC_H_

#include "ippdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== IPP Speech Bit Rate Definition ===================== */

typedef enum {
	IPP_SPCHBR_4750,
	IPP_SPCHBR_5150,
	IPP_SPCHBR_5900,
	IPP_SPCHBR_6700,
	IPP_SPCHBR_7400,
	IPP_SPCHBR_7950,
	IPP_SPCHBR_10200,
	IPP_SPCHBR_12200,
	IPP_SPCHBR_DTX,
	IPP_SPCHBR_5300,
	IPP_SPCHBR_6300
} IppSpchBitRate;

/* ========================== Structure Definition ========================= */

typedef struct {
	Ipp16s	adaptEnableFlag;		/* adaptation enable flag */
	Ipp32s	prevFltEnergy;			/* previous filtered signal energy */
	Ipp32s	prevNoiseLevel;			/* previous noise level */
	Ipp16s	hangoverCount;			/* count for hangover frames */
	Ipp16s	vadVoiceCount;			/* count for VAD voice frames */
} IppG723AVadState;

typedef struct {
	Ipp16s	sidLpcAutoCorrExp;		/* exponent of the autocorrelation */
									/* coefficient of SID LPC coefficients */
	Ipp16s	sidLpcAutoCorr[11];		/* SID LPC coefficients autocorrelation */
	Ipp16s	qSidGainIndex;			/* quantized SID gain index */
	Ipp16s	residualEnergy[3];		/* residual energy of previous 3 frames */
	Ipp16s	sumFrame;				/* summation frames number */
} IppG723ADtxState;

typedef struct {
	Ipp16s	pPrevSignalSublevel[9];	/* signal sublevel vector */
	Ipp16s	pPrevSignalLevel[9];	/* previous signal level vector */
	Ipp16s	pPrevAverageLevel[9];	/* average signal level */
	Ipp16s	pBkgNoiseEstimate[9];	/* background noise estimate vector */
	Ipp16s	pFifthFltState[6];		/* 5th order filters history */
	Ipp16s 	pThirdFltState[5];		/* 3rd order filters history */
	Ipp16s	burstCount;				/* burst counter */
	Ipp16s	hangCount;				/* hangover counter */
	Ipp16s	statCount;				/* stationarity counter */
	Ipp16s	vadReg;					/* intermediate vad decision */
	Ipp16s	complexHigh;			/* high for complex signal decision */	
	Ipp16s	complexLow;				/* low for ccomplex signal decision */
	Ipp16s	complexHangTimer;		/* complex hangover timer */
	Ipp16s	complexHangCount;		/* complex hangover counter */
	Ipp16s	complexWarning;			/* complex_warining flag */
	Ipp16s	corrHp;					/* High-pass filtered signal correlation */
	Ipp16s	pitchFlag;				/* pitch flag by pitch detection */
} IppGSMAMRVad1State;

typedef struct {
	Ipp32s	pEngyEstimate[16];		/* channel energy estimate vector of */
									/* current half-frame */
	Ipp32s	pNoiseEstimate[16];		/* channel noise estimiate vector of */
									/* current half-frame */
	Ipp16s	pLongTermEngyDb[16];	/* channel long-term log energy vector */ 
									/* of current half-frame */
	Ipp16s	preEmphasisFactor;		/* pre-emphasize factor */
	Ipp16s	updateCount;			/* update counter */
	Ipp16s	lastUpdateCount;		/* last update counter */
	Ipp16s	hysterCount;			/* hyster counter */
	Ipp16s	prevNormShift;			/* previous normalize shift bits */
	Ipp16s	shiftState;				/* previous half-frame shift state */	
	Ipp16s	forcedUpdateFlag;		/* forced update flag */
	Ipp16s	ltpSnr;					/* long-term peak SNR */
	Ipp16s	variabFactor;			/* background noise variablity factor */
	Ipp16s	negSnrBias;				/* negative SNR sensitivity Bias */
	Ipp16s	burstCount;				/* burst counter */
	Ipp16s	hangOverCount;			/* hangover counter */
	Ipp32s	frameCount;				/* frame counter */
} IppGSMAMRVad2State;

/* ========================== G.723.1/A Functions ========================== */

/* LP analysis */
IPPAPI(IppStatus, ippsAutoCorr_G723_16s,
	(const Ipp16s * pSrcSpch, Ipp16s * pResultAutoCorrExp, 
	Ipp16s * pDstAutoCorr))

IPPAPI(IppStatus, ippsLevinsonDurbin_G723_16s,
	(const Ipp16s * pSrcAutoCorr, Ipp16s * pValResultSineDtct, 
	Ipp16s * pResultResidualEnergy, Ipp16s * pDstLpc))

IPPAPI(IppStatus, ippsLPCToLSF_G723_16s,
	(const Ipp16s * pSrcLpc, const Ipp16s * pSrcPrevLsf, Ipp16s * pDstLsf))

IPPAPI(IppStatus, ippsLSFToLPC_G723_16s,
	(const Ipp16s * pSrcLsf, Ipp16s * pDstLpc))

IPPAPI(IppStatus, ippsLSFQuant_G723_16s32s,
	(const Ipp16s * pSrcLsf, const Ipp16s * pSrcPrevLsf, 
	Ipp32s * pResultQLsfIndex))

/* adaptive-codebook search */
IPPAPI(IppStatus, ippsOpenLoopPitchSearch_G723_16s,
	(const Ipp16s * pSrcWgtSpch, Ipp16s * pResultOpenDelay))

IPPAPI(IppStatus, ippsHarmonicSearch_G723_16s,
	(Ipp16s valOpenDelay, const Ipp16s * pSrcWgtSpch, 
	Ipp16s * pResultHarmonicDelay, Ipp16s * pResultHarmonicGain))

IPPAPI(IppStatus, ippsAdaptiveCodebookSearch_G723,
	(Ipp16s valBaseDelay, const Ipp16s * pSrcAdptTarget, 
	const Ipp16s * pSrcImpulseResponse, const Ipp16s * pSrcPrevExcitation, 
	const Ipp32s * pSrcPrevError, Ipp16s * pResultCloseLag, 
	Ipp16s * pResultAdptGainIndex, Ipp16s subFrame, Ipp16s sineDtct, 
	IppSpchBitRate bitRate))

IPPAPI(IppStatus, ippsDecodeAdaptiveVector_G723_16s,
	(Ipp16s valBaseDelay, Ipp16s valCloseLag, Ipp16s valAdptGainIndex,
	const Ipp16s * pSrcPrevExcitation, Ipp16s * pDstAdptVector,
	IppSpchBitRate bitRate))

/* fixed-codebook search */
IPPAPI(IppStatus, ippsToeplizMatrix_G723_16s,
	(const Ipp16s * pSrcImpulseResponse, Ipp16s * pDstMatrix))

IPPAPI(IppStatus, ippsMPMLQFixedCodebookSearch_G723,
	(Ipp16s valBaseDelay, const Ipp16s * pSrcImpulseResponse, 
	const Ipp16s * pSrcResidualTraget, Ipp16s * pDstFixedVector, 
	Ipp16s * pResultGrid, Ipp16s * pResultTrainDirac, 
	Ipp16s * pResultAmpIndex, Ipp16s * pResultAmplitude, 
	Ipp32s * pResultPosition,  Ipp16s subFrame))

IPPAPI(IppStatus, ippsACELPFixedCodebookSearch_G723_16s,
	(const Ipp16s * pSrcFixedCorr, const Ipp16s * pSrcMatrix, 
	Ipp16s * pDstFixedSign, Ipp16s * pDstFixedPosition, Ipp16s * pResultGrid, 
	Ipp16s * pDstFixedVector, Ipp16s * pSearchTimes))

/* filtering */
IPPAPI(IppStatus, ippsSynthesisFilter_G723_16s,
	(const Ipp16s * pSrcLpc, const Ipp16s * pSrcResidual, 
	Ipp16s * pSrcDstIIRState, Ipp16s * pDstSpch))

IPPAPI(IppStatus, ippsPitchPostFilter_G723_16s,
	(Ipp16s valBaseDelay, const Ipp16s * pSrcResidual, Ipp16s * pResultDelay, 
	Ipp16s * pResultPitchGain, Ipp16s * pResultScalingGain, Ipp16s subFrame, 
	IppSpchBitRate bitRate))

/* ============================ GSM-AMR Functions ========================== */

/* LP analysis */
IPPAPI(IppStatus, ippsAutoCorr_GSMAMR_16s32s,
	(const Ipp16s * pSrcSpch, Ipp32s * pDstAutoCorr, IppSpchBitRate mode))

IPPAPI(IppStatus, ippsLevinsonDurbin_GSMAMR,
	(const Ipp32s * pSrcAutoCorr, Ipp16s * pSrcDstLpc))

IPPAPI(IppStatus, ippsLPCToLSP_GSMAMR_16s,
	(const Ipp16s * pSrcLpc, const Ipp16s * pSrcPrevLsp, Ipp16s * pDstLsp))

IPPAPI(IppStatus, ippsLSPToLPC_GSMAMR_16s,
	(const Ipp16s * pSrcLsp, Ipp16s * pDstLpc))

IPPAPI(IppStatus, ippsLSPQuant_GSMAMR_16s,
	(const Ipp16s * pSrcLsp, Ipp16s * pSrcDstPrevQLsfResidual, 
	Ipp16s * pDstQLsp, Ipp16s * pDstQLspIndex, IppSpchBitRate mode))

/* adaptive-codebook search */
IPPAPI(IppStatus, ippsImpulseResponseTarget_GSMAMR_16s,
	(const Ipp16s * pSrcSpch, const Ipp16s * pSrcWgtLpc1, 
	const Ipp16s * pSrcWgtLpc2, const Ipp16s * pSrcQLpc, 
	const Ipp16s * pSrcSynFltState, const Ipp16s * pSrcWgtFltState,  
	Ipp16s * pDstImpulseResponse, Ipp16s * pDstLpResidual, 
	Ipp16s * pDstAdptTarget))

IPPAPI(IppStatus, ippsOpenLoopPitchSearchNonDTX_GSMAMR_16s,
	(const Ipp16s * pSrcWgtLpc1, const Ipp16s * pSrcWgtLpc2,
	const Ipp16s * pSrcSpch, Ipp16s * pValResultPrevMidPitchLag, 
	Ipp16s * pValResultVvalue, Ipp16s * pSrcDstPrevPitchLag, 
	Ipp16s * pSrcDstPrevWgtSpch, Ipp16s * pDstOpenLoopLag, 
	Ipp16s * pDstOpenLoopGain, IppSpchBitRate mode))

IPPAPI(IppStatus, ippsOpenLoopPitchSearchDTXVAD1_GSMAMR_16s,
	(const Ipp16s * pSrcWgtLpc1, const Ipp16s * pSrcWgtLpc2, 
	const Ipp16s * pSrcSpch, Ipp16s * pValResultToneFlag, 
	Ipp16s * pValResultPrevMidPitchLag, Ipp16s * pValResultVvalue, 
	Ipp16s * pSrcDstPrevPitchLag, Ipp16s * pSrcDstPrevWgtSpch, 
	Ipp16s * pResultMaxHpCorr, Ipp16s * pDstOpenLoopLag, 
	Ipp16s * pDstOpenLoopGain, IppSpchBitRate mode))

IPPAPI(IppStatus, ippsOpenLoopPitchSearchDTXVAD2_GSMAMR,
	(const Ipp16s * pSrcWgtLpc1, const Ipp16s * pSrcWgtLpc2, 
	const Ipp16s * pSrcSpch, Ipp16s * pValResultPrevMidPitchLag,
	Ipp16s * pValResultVvalue, Ipp16s * pSrcDstPrevPitchLag, 
	Ipp16s * pSrcDstPrevWgtSpch, Ipp32s * pResultMaxCorr, 
	Ipp32s * pResultWgtEnergy, Ipp16s * pDstOpenLoopLag, 
	Ipp16s * pDstOpenLoopGain, IppSpchBitRate mode))

IPPAPI(IppStatus, ippsAdaptiveCodebookSearch_GSMAMR_16s,
	(const Ipp16s * pSrcTarget, const Ipp16s * pSrcImpulseResponse, 
	const Ipp16s * pSrcOpenLoopLag, Ipp16s * pValResultPrevIntPitchLag,
	Ipp16s * pSrcDstExcitation, Ipp16s * pResultFracPitchLag, 
	Ipp16s * pResultAdptIndex, Ipp16s * pDstAdptVector, Ipp16s subFrame, 
	IppSpchBitRate mode))

IPPAPI(IppStatus, ippsAdaptiveCodebookDecode_GSMAMR_16s,
	(Ipp16s valAdptIndex, Ipp16s * pValResultPrevIntPitchLag, 
	Ipp16s * pValResultLtpLag, Ipp16s * pSrcDstExcitation, 
	Ipp16s * pResultIntPitchLag, Ipp16s * pDstAdptVector, Ipp16s subFrame, 
	Ipp16s bfi, Ipp16s inBackgroundNoise, Ipp16s voicedHangover,
	IppSpchBitRate mode))

/* fixed-codebook search */
IPPAPI(IppStatus, ippsAlgebraicCodebookSearch_GSMAMR_16s,
	(Ipp16s	valIntPitchLag,	Ipp16s valBoundQAdptGain, 
	const Ipp16s * pSrcFixedTarget, const Ipp16s * pSrcLtpResidual,
	Ipp16s * pSrcDstImpulseResponse, Ipp16s	* pDstFixedVector, 
	Ipp16s * pDstFltFixedVector, Ipp16s * pDstEncPosSign, 
	Ipp16s subFrame, IppSpchBitRate mode))

/* parameter decode */
IPPAPI(IppStatus, ippsQuantLSPDecode_GSMAMR_16s,
	(const Ipp16s * pSrcQLspIndex, Ipp16s * pSrcDstPrevQLsfResidual,
	Ipp16s * pSrcDstPrevQLsf, Ipp16s * pSrcDstPrevQLsp, Ipp16s * pDstQLsp, 
	Ipp16s bfi, IppSpchBitRate mode))

IPPAPI(IppStatus, ippsFixedCodebookDecode_GSMAMR_16s,
	(const Ipp16s * pSrcFixedIndex, Ipp16s * pDstFixedVector,
	Ipp16s subFrame, IppSpchBitRate	mode))

/* filtering */
IPPAPI(IppStatus, ippsPostFilter_GSMAMR_16s,
	(const Ipp16s * pSrcQLpc, const Ipp16s * pSrcSpch, 
	Ipp16s * pValResultPrevResidual, Ipp16s * pValResultPrevScalingGain, 
	Ipp16s * pSrcDstFormantFIRState, Ipp16s * pSrcDstFormantIIRState, 
	Ipp16s * pDstFltSpch, IppSpchBitRate mode))

/* voice activity detector/discontinuous transmission */
IPPAPI(IppStatus, ippsVAD1_GSMAMR_16s,
	(const Ipp16s * pSrcSpch, IppGSMAMRVad1State * pValResultVad1State,	
	Ipp16s * pResultVadFlag, Ipp16s	maxHpCorr, Ipp16s toneFlag))

IPPAPI(IppStatus, ippsVAD2_GSMAMR_16s,
	(const Ipp16s * pSrcSpch, IppGSMAMRVad2State * pValResultVad2State,
	Ipp16s * pResultVadFlag, Ipp16s ltpFlag))

IPPAPI(IppStatus, ippsEncDTXSID_GSMAMR_16s,
	(const Ipp16s * pSrcLspBuffer, const Ipp16s * pSrcLogEnergyBuffer, 
	Ipp16s * pValResultLogEnergyIndex, Ipp16s * pValResultDtxLsfRefIndex, 
	Ipp16s * pSrcDstDtxQLsfIndex, Ipp16s * pSrcDstPredQErr, 
	Ipp16s * pSrcDstPredQErrMR122, Ipp16s sidFlag))

IPPAPI(IppStatus, ippsEncDTXHandler_GSMAMR_16s,
	(Ipp16s * pValResultHangOverCount, Ipp16s * pValResultDtxElapseCount, 
	Ipp16s * pValResultUsedMode, Ipp16s * pResultSidFlag, Ipp16s vadFlag))

IPPAPI(IppStatus, ippsEncDTXBuffer_GSMAMR_16s,
	(const Ipp16s * pSrcSpch, const Ipp16s * pSrcLsp, 
	Ipp16s * pValResultUpdateIndex, Ipp16s * pSrcDstLspBuffer, 
	Ipp16s * pSrcDstLogEnergyBuffer))

IPPAPI(IppStatus, ippsDecDTXBuffer_GSMAMR_16s, 
	(const Ipp16s * pSrcSpch, const Ipp16s * pSrcLsf, 
	Ipp16s * pValResultUpdateIndex, Ipp16s * pSrcDstLsfBuffer, 
	Ipp16s * pSrcDstLogEnergyBuffer))

#ifdef __cplusplus
}
#endif

#endif /* _IPPSC_H_ */ 

/* End of file ippSC.h */
