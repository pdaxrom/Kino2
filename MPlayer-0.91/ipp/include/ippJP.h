/******************************************************************************
//             INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 2000-2001 Intel Corporation. All Rights Reserved.
//
//  Description:
//      Intel(R) Integrated Performance Primitives - JPEG header file.
//						Version 1.11
//
//      This file contains declarations specific to the JPEG codec.
//
********************************************************************************/
#ifndef _IPPJP_H_
#define _IPPJP_H_

#include "ippdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================== Intel IPP JPEG structure definiation ======================*/

/* ippJPEGENHuffTable */
typedef struct _IPPJPEGENHUFFTABLE
{
    Ipp8u  huffSize[256];	/* length of code for each symbol */
    Ipp16u huffCode[256];	/* code for each symbol */

}IppJPEGEnHuffTable;


/* ippJPEGDEHuffTable */
typedef struct _IPPJPEGDEHUFFTABLE
{
    /* 
    //Table with maximum value of Huffman code 
    //for each code lenth 
    */
    Ipp16u mincode[18];	
    /* 
    //Table with minimum value of Huffman code 
    //for each code lenth 
    */
    Ipp16u maxcode[18];		
    /* 
    //Table with index of 1st symbol of each code length in huffval.
    */
    Ipp16u valptr[18];  
    /* 
    // An 8-bit lookup table for fast Huffman decoding 
    */
    Ipp32u lookBitsVal[256];
    /* 
    // A list of 8-bit symble values 
    */
    Ipp16u huffVal[256];	

}IppJPEGDeHuffTable;


/*====================== Intel IPP JPEG API definiation ========================*/

/* 
//
//  Helper function  group
//
*/

/* 
//  Copy and pading function set
*/

/* Pading pixels for MCU in the boundary */
IPPAPI(IppStatus, ippiCopyExpand_8u_C3, (const Ipp8u *pSrc, 
                                        int srcStep,
                                        IppiSize srcSize,
                                        Ipp8u *pDst,
                                        int dstStep,
                                        IppiSize dstSize))

/* 
//  Color conversion function set
*/

/* CC: Convert MCU BGR to YCbCr with Level-Shift, the ouput data is interleave */
IPPAPI(IppStatus, ippiBGRToYCbCr444LS_MCU_8u16s_C3P3,  (const Ipp8u * pSrcBGR, 
							                            int srcStep, 
       									                Ipp16s * pDstMCU[3]))
IPPAPI(IppStatus, ippiBGRToYCbCr422LS_MCU_8u16s_C3P3,  (const Ipp8u * pSrcBGR, 
							                            int srcStep, 
       									                Ipp16s * pDstMCU[3]))
IPPAPI(IppStatus, ippiBGRToYCbCr411LS_MCU_8u16s_C3P3,  (const Ipp8u * pSrcBGR, 
							                            int srcStep, 
       									                Ipp16s * pDstMCU[3]))

/* CC: Convert MCU YCbCr to BGR with Level-Shift, the Input data is interleave */
IPPAPI(IppStatus, ippiYCbCr444ToBGRLS_MCU_16s8u_P3C3,  (const Ipp16s * pSrcMCU[3],
                                                        Ipp8u * pDstBGR, 
							                            int dstStep))
IPPAPI(IppStatus, ippiYCbCr422ToBGRLS_MCU_16s8u_P3C3, (const Ipp16s * pSrcMCU[3],
                                                        Ipp8u * pDstBGR, 
							                            int dstStep)) 
IPPAPI(IppStatus, ippiYCbCr411ToBGRLS_MCU_16s8u_P3C3,(const Ipp16s * pSrcMCU[3],
                                                        Ipp8u * pDstBGR, 
							                            int dstStep))


/* 
//  Level shift function set
*/

/* Level-shift from [0, 255] to [-128, 127] for one channel*/
IPPAPI(IppStatus, ippiLevelShiftSub128_8x8_8u16s_C1, (const Ipp8u *pSrc,
                                                  int srcStep,
                                                  Ipp16s *pDst))
IPPAPI(IppStatus, ippiLevelShiftSub128_8x8_8u16s_C1R, (const Ipp8u *pSrc,
                                                   int srcStep,
                                                   Ipp16s *pDst,
                                                   IppiSize roiSize))

/* Level-shift from [-128, 127] to [0, 255] for one channel*/
IPPAPI(IppStatus, ippiLevelShiftAdd128_8x8_16s8u_C1, (const Ipp16s *pSrc,
                                                  Ipp8u *pDst,
                                                  int dstStep))

IPPAPI(IppStatus, ippiLevelShiftAdd128_8x8_16s8u_C1R, (const Ipp16s *pSrc,
                                                       Ipp8u *pDst,
                                                       int dstStep,
                                                       IppiSize roiSize))

/*
//
// JPEG CODEC function group
//
*/

/*
// DCT & Quantization function set
*/

/* Forward DCT & Quantization */
IPPAPI(IppStatus, ippiDCTQuantFwdTableInit_JPEG_16u, (const Ipp16u *pSrcQuantTable,
                                                      Ipp16u *pDstQuantTable))

IPPAPI(IppStatus, ippiDCTQuantFwd_JPEG_16s, (const Ipp16s* pSrc, 
                                             Ipp16s *pDst, 
                                             const Ipp16u *pQuantTable))

IPPAPI(IppStatus, ippiDCTQuantFwd_JPEG_16s_I, (Ipp16s* pSrcDst, 
                                               const Ipp16u *pQuantTable))

IPPAPI(IppStatus, ippiDCTQuantFwd_Blocks_JPEG_16s, (const Ipp16s* pSrc, 
                                                   Ipp16s *pDst, 
                                                   int   blockCount,
                                                   const Ipp16u *pQuantTable))
IPPAPI(IppStatus, ippiDCTQuantFwd_Blocks_JPEG_16s_I, (Ipp16s* pSrcDst, 
                                                     int   blockCount,
                                                     const Ipp16u *pQuantTable))

/* Inverse DCT & Quantization */
IPPAPI(IppStatus, ippiDCTQuantInvTableInit_JPEG_16u32s, (const Ipp16u *pSrcQuantTable,
                                                         Ipp32s *pDstQuantTable))

IPPAPI(IppStatus, ippiDCTQuantInv_JPEG_16s, (const Ipp16s* pSrc, 
                                             Ipp16s *pDst, 
                                             const Ipp32s *pQuantTable))

IPPAPI(IppStatus, ippiDCTQuantInv_JPEG_16s_I, (Ipp16s* pSrcDst, 
                                               const Ipp32s *pQuantTable))

IPPAPI(IppStatus, ippiDCTQuantInv_Blocks_JPEG_16s, (const Ipp16s* pSrc, 
                                                    Ipp16s *pDst, 
                                                    int   blockCount,
                                                    const Ipp32s *pQuantTable))
IPPAPI(IppStatus, ippiDCTQuantInv_Blocks_JPEG_16s_I, (Ipp16s* pSrcDst, 
                                                      int   blockCount,
                                                      const Ipp32s *pQuantTable))
/*
// Huffman coding function set
*/

/* Generate Humman table for encoder */
IPPAPI(IppStatus, ippiEncodeHuffmanTableInit_JPEG_8u, (const Ipp8u *pHuffBits,
                                                       const Ipp8u *pHuffValue,
                                                       IppJPEGEnHuffTable *pHuffTable))

/* Encoder for baseline */
IPPAPI(IppStatus, ippiEncodeHuffman_Direct_JPEG_16s1u, ( const Ipp16s *pSrc, Ipp8u  *pDst,  
                                                        int   *pDstBitsLen, Ipp16s *pDCPred,
                                                        const IppJPEGEnHuffTable *pDCHuffTable,
                                                        const IppJPEGEnHuffTable *pACHuffTable))

/* Encoder for progressive */
IPPAPI(IppStatus, ippiEncodeHuffman_Direct_JPEG_DCFirst_16s1u, ( const Ipp16s *pSrc,
                                                                Ipp8u        *pDst,  
                                                                int          *pDstBitsLen,
                                                                Ipp16s       *pDCPred,
                                                                int          al,
                                                                const IppJPEGEnHuffTable *pDCHuffTable))

IPPAPI(IppStatus, ippiEncodeHuffman_Direct_JPEG_DCRefine_16s1u, (const Ipp16s *pSrc,
                                                         Ipp8u        *pDst,  
                                                         int          *pDstBitsLen,
                                                         int          al))

IPPAPI(IppStatus, ippiEncodeHuffman_Direct_JPEG_ACFirst_16s1u, (const Ipp16s *pSrc, Ipp8u *pDst,  
                                                               int   *pDstBitsLen, int   *pEOBRun,
                                                               int   ss,           int   se,
                                                               int   al, 
                                                               const IppJPEGEnHuffTable *pACHuffTable))

IPPAPI(IppStatus, ippiEncodeHuffman_Direct_JPEG_ACRefine_16s1u,( const Ipp16s *pSrc, Ipp8u *pDst,  
                                                                int   *pDstBitsLen, int   *pEOBRun,
                                                                Ipp8u  *pBitBuffer, int   *pBELen,
                                                                int             ss, int    se,
                                                                int             al,
                                                                const IppJPEGEnHuffTable *pACHuffTable))

IPPAPI(IppStatus, ippiEncodeHuffman_Direct_JPEG_ACFinal, (int         srcEOBRun,
                                                        const Ipp8u  *pBitBuffer,
                                                        int          nBELen,
                                                        Ipp8u        *pDst,  
                                                        int          *pDstBitsLen,
                                                        const IppJPEGEnHuffTable 
                                                                     *pACHuffTable))

/* Generate Humman table for decoder */
IPPAPI(IppStatus, ippiDecodeHuffmanTableInit_JPEG_8u, ( const Ipp8u *pHuffBits,
                                                        const Ipp8u *pHuffValue,
                                                        IppJPEGDeHuffTable *pHuffTable))
/* Decoder for baseline */
IPPAPI(IppStatus, ippiDecodeHuffman_Direct_JPEG_1u16s,(const Ipp8u *pSrc, int    *pSrcBitsLen,
                                                      Ipp16s      *pDst, Ipp16s *pDCPred,
                                                      int      *pMarker, Ipp32u *pPrefetchedBits,
                                                      int      *pNumValidPrefetchedBits,
                                                      const IppJPEGDeHuffTable *pDCHuffTable,
                                                      const IppJPEGDeHuffTable *pACHuffTable))

/* Decoder for progressive */
IPPAPI(IppStatus, ippiDecodeHuffman_Direct_JPEG_DCFirst_1u16s,(const Ipp8u *pSrc, int    *pSrcBitsLen,
                                                              Ipp16s      *pDst, Ipp16s *pDCPred,
                                                              int      *pMarker, Ipp32u *pPrefetchedBits,
                                                              int      *pNumValidPrefetchedBits,
                                                              int       al,
                                                              const IppJPEGDeHuffTable *pDCHuffTable))

IPPAPI(IppStatus, ippiDecodeHuffman_Direct_JPEG_DCRefine_1u16s,(const Ipp8u *pSrc,
                                                               int         *pSrcBitsLen,
                                                               Ipp16s      *pDst,
                                                               int         *pMarker,
                                                               Ipp32u      *pPrefetchedBits,
                                                               int         *pNumValidPrefetchedBits,
                                                               int         al))

IPPAPI(IppStatus, ippiDecodeHuffman_Direct_JPEG_ACFirst_1u16s,(const Ipp8u *pSrc, int *pSrcBitsLen,
                                                              Ipp16s      *pDst, int *pEOBRun,
                                                              int      *pMarker, Ipp32u *pPrefetchedBits,
                                                              int *pNumValidPrefetchedBits,
                                                              int         ss,    int         se,
                                                              int         al,
                                                              const IppJPEGDeHuffTable *pACHuffTable))

IPPAPI(IppStatus, ippiDecodeHuffman_Direct_JPEG_ACRefine_1u16s,(const Ipp8u *pSrc, int    *pSrcBitsLen,
                                                               Ipp16s      *pDst, int    *pEOBRun,
                                                               int      *pMarker, Ipp32u *pPrefetchedBits,
                                                               int      *pNumValidPrefetchedBits,
                                                               int      ss,       int   se,
                                                               int      al,
                                                               const IppJPEGDeHuffTable *pACHuffTable))

#ifdef __cplusplus
}
#endif

#endif /* _IPPJP_H_ */ 

/* End of file */
