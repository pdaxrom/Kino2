/********************************************************************************
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 1999 Intel Corporation. All Rights Reserved.
//
//
//  Description:
//     Intel(R) Integrated Performance Primitives.
//     This file contains declarations specific to the image processing domain.
//                             Version 1.11
********************************************************************************/

#if !defined( __IPPIP_H__ ) 
#define __IPPIP_H__

#ifndef __IPPDEFS_H__
  #include "ippdefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    ippMskSize1x3 = 13,
    ippMskSize1x5 = 15,
    ippMskSize3x1 = 31,
    ippMskSize3x3 = 33,
    ippMskSize5x1 = 51,
    ippMskSize5x5 = 55
} IppiMaskSize;

typedef enum {
    ippAlphaOver,
    ippAlphaIn,
    ippAlphaOut,
    ippAlphaATop,
    ippAlphaXor,
    ippAlphaPlus,
    ippAlphaOverPremul,
    ippAlphaInPremul,
    ippAlphaOutPremul,
    ippAlphaATopPremul,
    ippAlphaXorPremul,
    ippAlphaPlusPremul
} IppiAlphaType;

typedef enum {
    ippDitherNone,
    ippDitherFS,
    ippDitherJJN,
    ippDitherStucki,
    ippDitherBayer
} IppiDitherType;



/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  Copy/Set Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippiSet_8u_C1R()
//             ippiSet_8u_C3R()
//             ippiSet_8u_AC4R()
//
// Purpose:    Set Image by the constant
//
// Returns:
//    ippStsNoErr       no error
//    ippStsNullPtrErr  NULL==pDst
//    ippStsStepErr     dstSTep <=0
//    ippStsSizeErr     dstRoiSize.width<1 || dstRoiSize.height<1
//
// Parameters:
//    value          value of the constant (or pointer to the array of constants)
//    pDst           pointer to the target image ROI
//    dstStep        target scan line size (bytes)
//    dstRoiSize     size of target ROI
//
*/
IPPAPI(IppStatus, ippiSet_8u_C1R, (
               Ipp8u value, Ipp8u* pDst, int dstStep,
               IppiSize dstRoiSize))
IPPAPI(IppStatus, ippiSet_8u_C3R, (
               const Ipp8u value[3], Ipp8u* pDst, int dstStep,
               IppiSize dstRoiSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippiCopy_8u_C1R()
//             ippiCopy_8u_C3R()
//             ippiCopy_8u_AC4R()
//
// Purpose:    Copy Image
//
// Returns:
//    ippStsNoErr       no error
//    ippStsNullPtrErr  NULL==pSrc || NULL==pDst
//    ippStsStepErr     srcSTep<=0 || dstSTep <=0
//    ippStsSizeErr     dstRoiSize.width<1 || dstRoiSize.height<1
//
// Parameters:
//    pSrc           pointer to the source image ROI
//    srcStep        source scan line size (bytes)
//    pDst           pointer to the target image ROI
//    dstStep        target scan line size (bytes)
//    dstRoiSize     size of target ROI
//
*/
IPPAPI(IppStatus, ippiCopy_8u_C1R, (
               const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep,
               IppiSize dstRoiSize))
IPPAPI(IppStatus, ippiCopy_8u_C3R, (
               const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep,
               IppiSize dstRoiSize))


/* /////////////////////////////////////////////////////////////////////////////
//                  Filtering Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
// Name:   ippiFilterBox
//
// Purpose:    Applies simple neighborhood averaging filter to blur the image
//
// Arguments:
//   pSrc         - sourse image data(point to pixel (0,0)).
//   srcStep      - step in src
//   pDst         - resultant image data.
//   dstStep      - step in dst
//   dstRoiSize   - region of interest of dst
//   maskSize     - Number of columns and rows in the neighbourhood(cell)to use.
//   anchor       - The [x,y] coordinates of the anchor cell in the neighbourhood.
//
// Return:              Reason
//   ippStsNoErr,       no errors
//   ippStsNullPtrErr,  pSrc == NULL or pDst == NULL
//   ippStsStep,        srdStep<=0 or dstStep<=0
//   ippStsSizeErr,     dstRoiSize.width<=0 or dstRoiSize.height<=0
//   ippStsAnchorErr    width or height of images is less  zero.
//   ippStsMaskSizeErr  maskSize.width<=1 or maskSize.height<=1
//
*F*/
IPPAPI(IppStatus, ippiFilterBox_8u_C1R,(
                     const Ipp8u* pSrc,int srcStep ,
                           Ipp8u* pDst,int dstStep,IppiSize dstRoiSize,
                           IppiSize maskSize, IppiPoint anchor))
IPPAPI(IppStatus, ippiFilterBox_8u_C3R,(
                     const Ipp8u* pSrc,int srcStep ,
                           Ipp8u* pDst,int dstStep,IppiSize dstRoiSize,
                           IppiSize maskSize, IppiPoint anchor))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterColumn
//             ippiFilterRow
//
//  Purpose:   ROI-oriented Column/Row FIR Filter.
//
//  Arguments:
//    pSrc        pointer to the source ROI
//    srcStep     size of source image scan-line
//    pDst        pointer to the target ROI
//    dstStep     size of target image scan-line
//    dstRoiSize  size of the target ROI
//    pKernel     pointer to the column FIR filter
//    kernelSize  filter length
//    anchor      filter anchor
//    divider     output divider
//
//  Return:                Reason:
//    ippStsNullPtrErr,    pSrc == NULL, pDst == NULL or pKernel==NULL
//    ippStsStep,          srdStep<=0 or dstStep<=0
//    ippStsSizeErr,       dstRoiSize.width<=0 or dstRoiSize.height<=0
//                         kernel too short (<2)
//    ippStsAnchorErr      anchor out of kernel
//    ippStsScaleRangeErr  divider <= 0
//    ippStsMemAllocErr    memory allocation problems
//    ippStsNoErr          no problems
//
//  Note:
//    Filter output would be saturated
*/
IPPAPI(IppStatus, ippiFilterColumn_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     const Ipp32s* pKernel, int kernelSize, int anchor,
                     int divider))
IPPAPI(IppStatus, ippiFilterColumn_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     const Ipp32s* pKernel, int kernelSize, int anchor,
                     int divider))

IPPAPI(IppStatus, ippiFilterRow_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     const Ipp32s* pKernel, int kernelSize, int anchor,
                     int divider))
IPPAPI(IppStatus, ippiFilterRow_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     const Ipp32s* pKernel, int kernelSize, int anchor,
                     int divider))

/* //////////////////////////////////////////////////////////////////////
// Name:       ippiFilter
//
// Purpose:    IPPi 2D FIR Filtering of an image ROI
//
//  Arguments:
//    pSrc           pointer to the source image ROI
//    srcStep        source scan line size (bytes)
//    pDst           pointer to the target image ROI
//    dstStep        target scan line size (bytes)
//    dstRoiSize     size of target ROI
//    pKernel        pointer to the integer kernel
//    kernelSize     size of kernel
//    kernelAnchor   kernel anchor coordinates
//    divider        output divider
//
//  Return:                Reason:
//    ippStsNullPtrErr     pointer(s) to the source/destination ROI or kernel is NULL
//    ippStsStep,          srdStep<=0 or dstStep<=0
//    ippStsSizeErr        illegal ROI sizes
//                         kernelSize<2
//    ippStsAnchorErr      anchor out of kernel
//    ippStsScaleRangeErr  divider<=0
//    ippStsMemAllocErr    memory allocation problems
//    ippStsNoErr          no problems
*/
IPPAPI(IppStatus, ippiFilter_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     const Ipp32s* pKernel, IppiSize kernelSize, IppiPoint kernelAnchor,
                     int divider))
IPPAPI(IppStatus, ippiFilter_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     const Ipp32s* pKernel, IppiSize kernelSize, IppiPoint kernelAnchor,
                     int divider))

/* /////////////////////////////////////////////////////////////////////////////
//                   Median Filters
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterMedian
//
//  Purpose:   Apply Median/ColorMedian filter to ROI of 3-channels 8u Image
//
//  Arguments:
//    pSrc           pointer to the source image ROI
//    srcStep        source scan line size (bytes)
//    pDst           pointer to the target image ROI
//    dstStep        target scan line size (bytes)
//    dstRoiSize     size of target ROI
//    maskSize       determines size of the neighborhood in pixels to use
//    anchor         anchor location
//
//  Return:             Reason:
//    ippStsNoErr       no error
//    ippStsNullPtrErr  NULL==pSrc or NULL==pDst
//    ippStsStepErr     srcStep<=0 or dstStep<=0
//    ippStsSizeErr     roiSize<{1,1}
//    ippStsMaskSizeErr maskSize<{0,0}
//                      or maskSize has an even size
//    ippStsAnchorErr   anchor out of mask
*/
IPPAPI(IppStatus, ippiFilterMedian_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize,
                     IppiSize maskSize, IppiPoint anchor))
IPPAPI(IppStatus, ippiFilterMedian_8u_C3R, (
                  const Ipp8u* pSrc, int srcStep,
                        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiSize maskSize, IppiPoint anchor))

IPPAPI(IppStatus, ippiFilterMedianColor_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                     IppiMaskSize mask))



/* /////////////////////////////////////////////////////////////////////////////
//                  Arithmetic & Logical Functions
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:     ippiAddC,       ippiAdd
//             ippiSubC,       ippiSub
//             ippiMulC,       ippiMul
//             ippiMulCScale,  ippiMulScale
//             ippiSqr
//
//  Purpose:   Arithmetic Operations upon every element
//             of the source image ROI
//
//  Arguments:
//    pSrc                 pointer to the source ROI
//    pSrc1                pointer to the first source ROI
//    pSrc2                pointer to the second source ROI
//    pDst                 pointer to the destination ROI
//    srcStep,dstStep,     scan line size (bytes)
//    src1Step,src2Step    of the source/destination image
//    value                constant operand
//    roiSize              size of the image ROI
//    scaleFactor          scale factor value
//
//  Return:                Reason:
//    ippStsNullPtrErr     pointer(s) to the source/destination ROI is NULL
//    ippStsSizeErr        ROI sizes are negative or zero
//    ippStsNoErr          no problems
//
//  Note:
//    AddC(v,X,Y)    :  Y[n] = X[n] + v
//    Add(X,Y,Z)     :  Z[n] = Y[n] + X[n]
//
//    SubC(v,X,Y)    :  Y[n] = X[n] - v
//    Sub(X,Y,Z)     :  Z[n] = Y[n] - X[n]
//
//    MulC(v,X,Y)    :  Y[n] = X[n] * v
//    Mul(X,Y,Z)     :  Z[n] = Y[n] * X[n]
//
//    MulCScale(v,X,Y)  :  Y[n] = ( X[n] * v ) / IPP_MAX_8U
//    MulScale(X,Y,Z)   :  Z[n] = ( Y[n] * X[n] ) / IPP_MAX_8U
//
//    Sqr(X,Y,Z)     :  Y[n] = X[n] * X[n]
//
*/
IPPAPI(IppStatus, ippiAddC_8u_C1RSfs, (
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C1RSfs, (
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C1RSfs, (
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulCScale_8u_C1R,(
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiAddC_8u_C3RSfs, (
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C3RSfs, (
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C3RSfs, (
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulCScale_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiAdd_8u_C1RSfs,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C1RSfs,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C1RSfs,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst,  int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulScale_8u_C1R,(
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst,  int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSqr_8u_C1RSfs, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiAdd_8u_C3RSfs,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C3RSfs,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst,  int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C3RSfs,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst,  int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulScale_8u_C3R,(
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst,  int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSqr_8u_C3RSfs, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:     ippiAndC, ippiAnd
//             ippiOrC,  ippiOr
//             ippiXorC, ippiXor
//                       ippiNot
//                       ippiRShiftC
//                       ippiLShiftC
//
//  Purpose:   Logical Operations upon every element of
//             the source image ROI
//
//  Arguments:
//    pSrc                 pointer to the source ROI
//    pSrc1                pointer to the first source ROI
//    pSrc2                pointer to the second source ROI
//    pDst                 pointer to the destination ROI
//    srcStep,dstStep,     scan line size (bytes)
//    src1Step,src2Step     of the source/destination image
//    value                constant operand
//    roiSize              size of the image ROI
//
//  Return:                Reason:
//    ippStsNullPtrErr        pointer(s) to the source/destination ROI is NULL
//    ippStsSizeErr        ROI sizes are negative or zero
//    ippStsNoErr             no problems
//
//  Note:
//    AndC(v,X,Y)    :  Y[n] = X[n] & v
//    And(X,Y,Z)     :  Z[n] = Y[n] & X[n]
//
//    OrC(v,X,Y)     :  Y[n] = X[n] | v
//    Or(X,Y,Z)      :  Z[n] = Y[n] | X[n]
//
//    XorC(v,X,Y)    :  Y[n] = X[n] ^ v
//    Xor(X,Y,Z)     :  Z[n] = Y[n] ^ X[n]
//
//    Xor(X,Y)       :  Y[n] = ~X[n]
//
//    RShiftC(X,Y,v)  :  Y[n] = X[n] >> v
//    LShiftC(X,Y,v)  :  Y[n] = X[n] << v
*/
IPPAPI(IppStatus, ippiAndC_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C1R,  (
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep, Ipp8u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiAndC_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C3R,  (
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiAnd_8u_C1R, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C1R,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C1R, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C1R,(
                     const Ipp8u* pSrc, int srcStep, Ipp32u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C1R,(
                     const Ipp8u* pSrc, int srcStep, Ipp32u value,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiAnd_8u_C3R, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C3R,  (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C3R, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep, const Ipp32u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep, const Ipp32u value[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))



/* /////////////////////////////////////////////////////////////////////////////
//                  Linear Transforms Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                   DCT Transform and other JPEG support functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8Fwd_16s_C1()
//             ippiDCT8x8Inv_16s_C1()
//
//  Purpose:   Forward/Inverse Cosine 2D Transform of 8x8.
//
//  Arguments:
//    pSrc     pointer to the source image
//    pDst     pointer to the target image
//
//  Return:          Reason:
//    ippStsNullPtrErr  pointer(s) to the source/destination is NULL
//    ippStsNoErr       no problems
//
*/
IPPAPI(IppStatus,ippiDCT8x8Fwd_16s_C1, (const Ipp16s* pSrc, Ipp16s* pDst))
IPPAPI(IppStatus,ippiDCT8x8Inv_16s_C1, (const Ipp16s* pSrc, Ipp16s* pDst))


/* /////////////////////////////////////////////////////////////////////////////
//                   Fast Fourie Transform
///////////////////////////////////////////////////////////////////////////// */

#if !defined( _OWN_BLDPCS )

/* Real\Ccs 2D FFT context Definition */
struct FFT2DSpec_R_8u;
typedef struct FFT2DSpec_R_8u  IppiFFTSpec_R_8u;

#endif /* _OWN_BLDPCS */


/* //////////////////////////////////////////////////////////////////////
// Name:       ippiFFTGetSpecSize_8u
//             ippiFFTInit_R_8u
//             ippiFFTInitAlloc_R_8u
//             ippiFFTFree_R_8u
//
// Purpose:    Create/Remove 2D FFT Context of Real Data
//
//  Arguments:
//    xOrder   x-direction order
//    yOrder   y-direction order
//    flag     transform normalize flag
//    hint     algorithm hint
//    pCtx     address of pointer to the created 2D FFT Context
//
//  Return:                   Reason:
//    ippStsNoErr             no problem - context was created/removed
//    ippStsNullPtrErr        NULL pointer
//    ippStsFftOrderErr       illegal xOrder(yOrder) value
//    ippStsMemAllocErr       memory allocation pronlem has occured
//    ippStsContextMatchErr   mismatch context ID
*/
IPPAPI(IppStatus, ippiFFTGetSpecSize_R_8u, (
                     int xOrder, int yOrder, IppHintAlgorithm hint, int* pSize))
IPPAPI(IppStatus, ippiFFTInit_R_8u, (IppiFFTSpec_R_8u* pCtx,
                     int xOrder, int yOrder, int flag, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiFFTInitAlloc_R_8u, (IppiFFTSpec_R_8u** pCtx,
                     int xOrder, int yOrder, int flag, IppHintAlgorithm hint))
IPPAPI (IppStatus, ippiFFTFree_R_8u, (IppiFFTSpec_R_8u* pCtx))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFFTGetBufSize_R_8u
//
//  Purpose:   Returns size (bytes) of buffer for internal purpose
//
//  Arguments:
//    pCtx     pointer to the context
//    pSize    pointer to the buffer size (in bytes)
//
//  Return:                Reason:
//    ippStsNullPtrErr        NULL pointer
//    ippStsContextMatchErr   mismatch context ID
//    ippStsNoErr             no problem
*/
IPPAPI(IppStatus, ippiFFTGetBufSize_R_8u, (const IppiFFTSpec_R_8u* pCtx, int* pSize))

/* //////////////////////////////////////////////////////////////////////
// Name:       ippiFFTFwd_RToPack
//
// Purpose:    Forward/Reverse FFT of/to Real Image.
//
//  Arguments:
//    pCtx           pointer to the context
//    pSrc           pointer to the source image
//    srcStep        source image scanline (bytes)
//    pDst           pointer to the target image
//    dstStep        target image scanline (bytes)
//    scaleFactor    scale factor value
//    pBuffer        pointer to the buffer
//
//  Return:                   Reason:
//    ippStsNullPtrErr        NULL pointer
//    ippStsStepErr           srcStep<=0 or dstStep<=0
//    ippStsContextMatchErr   mismatch context ID
//    ippStsNoErr             no problem
//
//  Notes:
//    ippiFFTFwd_RToPack provide tansform from Real to the Pack Format data
//    ippiFFTInv_PackToR provide tansform from Pack Format to the Real data
*/
IPPAPI(IppStatus, ippiFFTFwd_RToPack_8u32s_C1R,(
                     const Ipp8u* pSrc, int srcStep,
                           Ipp32s* pDst, int dstStep,
                     const IppiFFTSpec_R_8u* pCtx,
                     int scaleFactor, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFFTFwd_RToPack_8u32s_C3R,(
                     const Ipp8u* pSrc, int srcStep,
                           Ipp32s* pDst, int dstStep,
                     const IppiFFTSpec_R_8u* pCtx,
                     int scaleFactor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFFTInv_PackToR_32s8u_C1RSfs,(
                     const Ipp32s* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep,
                     const IppiFFTSpec_R_8u* pCtx,
                     int scaleFactor, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFFTInv_PackToR_32s8u_C3RSfs,(
                     const Ipp32s* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep,
                     const IppiFFTSpec_R_8u* pCtx,
                     int scaleFactor, Ipp8u* pBuffer))



/* /////////////////////////////////////////////////////////////////////////////
//                  Color Conversion Functions
///////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
//  Name:      ippiColorTwistQ14
//
//  Purpose:   Apply color twist matrix of 2D buffer.
//
//  Arguments:
//    pSrc     pointer to the source image ROI
//    srcStep  source image scanline (bytes)
//    pDst     pointer to the target image ROI
//    dstStep  target image scanline (bytes)
//    twist    color twist matrix (all elements mutiplied by 2^14)
//    imgSize  ROI size
//
//  Return:                Reason:
//    ippStsNullPtrErr        NULL pointer
//    ippStsSizeErr        illegal ROI size
//    ippStsNoErr             no problem
*/
IPPAPI(IppStatus, ippiColorTwistQ14_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize,
                     const Ipp32s twist_Q14[3][4]))

/* //////////////////////////////////////////////////////////////////////////// */

/* XYZ */
IPPAPI (IppStatus, ippiRGBToXYZ_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiXYZToRGB_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))

/* YCC */
IPPAPI (IppStatus, ippiRGBToYCC_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiYCCToRGB_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))

/* LUV */
IPPAPI (IppStatus, ippiRGBToLUV_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiLUVToRGB_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))

/* HSV */
IPPAPI (IppStatus, ippiRGBToHSV_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiHSVToRGB_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))

/* HLS */
IPPAPI (IppStatus, ippiRGBToHLS_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiHLSToRGB_8u_C3R, (
                     const Ipp8u *pSrc, int srcStep,
                           Ipp8u *pDst, int dstStep, IppiSize roiSize))

/* Gamma */
IPPAPI (IppStatus, ippiGammaFwd_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiGammaInv_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

/* Gray */
IPPAPI (IppStatus, ippiRGBToGray_8u_C3C1R, (
                     const Ipp8u* pSrc,int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiColorToGrayQ14_8u_C3C1R,(
                     const Ipp8u* pSrc,int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize,
                     const Ipp32s coef_Q14[3]))


/* /////////////////////////////////////////////////////////////////////////////
//  Name: ippiRGBToYCbCr_8u_C3R, ippiYCbCrToRGB_8u_C3R.
//  Purpose:    Convert RGB Image to and from YCbCr Image.
//  Arguments:
//     pSrc - Pointer to the source image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     pDst - Pointer to the resultant image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     roiSize - region of interest in pixels.
//     srcStep - step in bytes through source image to jump on the next line
//     dstStep - step in bytes through destination image to jump on the next line
//  Returns:
//           ippStsNullPtrErr  if src == NULL or dst == NULL
//           ippStsStepErr,    if srcStep or dstStep is less or equal zero
//           ippStsSizeErr     if roiSize.width <= 0 || roiSize.height <= 0
//           ippStsNoErr       else
//  Reference:
//      Jack Keith
//      Video Demystified:a handbook for the digital engineer, 2nd ed.
//      1996.pp.(42-43)
//
//  The YCbCr color space was developed as part of Recommendation ITU-R BT.601
//  (formely CCI 601). Y is defined to have a nominal range of 16 to 235;
//  Cb and Cr are defined to have a range of 16 to 240, with 128 equal to zero.
//  If the gamma-corrected RGB(R'G'B') image has a range 0 .. 255, as is commonly
//  found in computer system (and in our library), the following equations may be
//  used:
//
//       Y  =  0.257*R' + 0.504*G' + 0.098*B' + 16
//       Cb = -0.148*R' - 0.291*G' + 0.439*B' + 128
//       Cr =  0.439*R' - 0.368*G' - 0.071*B' + 128
//
//       R' = 1.164*(Y - 16) + 1.596*(Cr - 128 )
//       G' = 1.164*(Y - 16) - 0.813*(Cr - 128 )- 0.392*( Cb - 128 )
//       B' = 1.164*(Y - 16) + 2.017*(Cb - 128 )
//
//   Note that for the YCbCr-to-RGB equations, the RGB values must be saturated
//   at the 0 and 255 levels due to occasional excursions outside the nominal
//   YCbCr ranges.
//
*/
IPPAPI(IppStatus, ippiRGBToYCbCr_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYCbCrToRGB_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name: ippiRGBToYCbCr422_8u_C3C2R,ippiYCbCr422ToRGB_8u_C2C3R.
//  Purpose:    Convert RGB Image to and from YCbCr Image.
//  Arguments:
//     pSrc - Pointer to the source image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     pDst - Pointer to the resultant image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     roiSize - region of interest in pixels.
//     srcStep - step in bytes through source image to jump on the next line
//     dstStep - step in bytes through destination image to jump on the next line
//  Returns:
//           ippStsNullPtrErr  if src == NULL or dst == NULL
//           ippStsStepErr,    if srcStep or dstStep is less or equal zero
//           ippStsSizeErr     if roiSize.width <= 0 || roiSize.height <= 0
//           ippStsNoErr       else
//  Reference:
//      Jack Keith
//      Video Demystified: a handbook for the digital engineer, 2nd ed.
//      1996.pp.(42-43)
//
//  The YCbCr color space was developed as part of Recommendation ITU-R BT.601
//  (formely CCI 601). Y is defined to have a nominal range of 16 to 235;
//  Cb and Cr are defined to have a range of 16 to 240, with 128 equal to zero.
//  The function ippiRGBToYCbCr422_8u_P3C2R uses 4:2:2 sampling format.For every
//  two  horisontal Y samples, there is one Cb and Cr sample.
//  Each pixel in the input RGB image is of 24 bit depth. Each pixel in the
//  output YCbCr image is of 16 bit depth. Sequence of bytes in the output
//  image is
//               Y0 Y1 Y2 Y3 .. Yw-1 <-8 bits   \ one  scan line.
//               Cb Cr Cb Cr .. Cb   <-8 bits   /
//
//  If the gamma-corrected RGB(R'G'B') image has a range 0 .. 255, as is commonly
//  found in computer system (and in our library), the following equations may be
//  used:
//
//       Y  =  0.257*R' + 0.504*G' + 0.098*B' + 16
//       Cb = -0.148*R' - 0.291*G' + 0.439*B' + 128
//       Cr =  0.439*R' - 0.368*G' - 0.071*B' + 128
//
//       R' = 1.164*(Y - 16) + 1.596*(Cr - 128 )
//       G' = 1.164*(Y - 16) - 0.813*(Cr - 128 )- 0.392*( Cb - 128 )
//       B' = 1.164*(Y - 16) + 2.017*(Cb - 128 )
//
//   Note that for the YCbCr-to-RGB equations, the RGB values must be saturated
//   at the 0 and 255 levels due to occasional excursions outside the nominal
//   YCbCr ranges.
//
*/
IPPAPI(IppStatus, ippiRGBToYCbCr422_8u_C3C2R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst, int dstStep,IppiSize roiSize))
IPPAPI(IppStatus, ippiYCbCr422ToRGB_8u_C2C3R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst, int dstStep,IppiSize roiSize))

/*********/
/* YUV   */
/*********/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiRGBToYUV_8u_C3R,  ippiYUVToRGB_8u_C3R.
//              ippiRGBToYUV_8u_C3P3R,ippiYUVToRGB_8u_P3C3R.
//  Purpose:    Convert a RGB image to and from an YUV format image.
//  Arguments:
//     pSrc - Pointer to the source image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     pDst - Pointer to the resultant image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     roiSize - region of interest in pixels.
//     srcStep - step in bytes through source image to jump on the next line
//     dstStep - step in bytes through destination image to jump on the next line
//  Returns:
//           ippStsNullPtrErr  if src == NULL or dst == NULL
//           ippStsStepErr,    if srcStep or dstStep is less or equal zero
//           ippStsSizeErr     if roiSize.width <= 0 || roiSize.height <= 0
//           ippStsNoErr       else
//  Reference:
//      Jack Keith
//      Video Demystified: a handbook for the digital engineer, 2nd ed.
//      1996.pp.(40-41)
//
//     The YUV color space is the basic color space used by the PAL , NTSC , and
//  SECAM composite color video standarts.
//
//  The basic equations to convert between gamma-corrected RGB(R'G'B')and YUV are:
//
//       Y' =  0.299*R' + 0.587*G' + 0.114*B'
//       U  = -0.147*R' - 0.289*G' + 0.436*B' = 0.492*(B' - Y' )
//       V  =  0.615*R' - 0.515*G' - 0.100*B' = 0.877*(R' - Y' )
//
//       R' = Y' + 1.140 * V
//       G' = Y' - 0.394 * U - 0.581 * V
//       B' = Y' + 2.032 * U
//
//     For digital RGB values with the range [0 .. 255], Y has the range [0..255],
//   U the range [-112 .. +112],V the range [-157..+157].
//
//   These equations are usually scaled to simplify the implementation in an actual
//   NTSC or PAL digital encoder or decoder.
//
*/
IPPAPI(IppStatus, ippiRGBToYUV_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUVToRGB_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRGBToYUV_8u_C3P3R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst[3], int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUVToRGB_8u_P3C3R,(
                     const Ipp8u* const pSrc[3], int srcStep,
                           Ipp8u* pDst,int dstStep, IppiSize roiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiRGBToYUV422_8u_C3P3R, ippiYUV422ToRGB_8u_P3C3R.
//              ippiRGBToYUV420_8u_C3P3R, ippiYUV420ToRGB_8u_P3C3R.
//              ippiRGBToYUV422_8u_C3R,   ippiYUV422ToRGB_8u_C3R.
//  Purpose:    Convert a RGB image to and from an YUV format image.
//  Arguments:
//     pSrc - Pointer to the source image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     pDst - Pointer to the resultant image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     roiSize - region of interest in pixels.
//     srcStep - step in bytes through source image to jump on the next line(for pixel-order data).
//               An array of step to separate source color planes (in case of plane-order data).
//     dstStep - step in bytes through destination image to jump on the next line(for pixel-order data).
//               An array of step to separate resultant color planes (in case of plane-order data).
//  Returns:
//           ippStsNullPtrErr  if src == NULL or dst == NULL
//           ippStsStepErr,    if srcStep or dstStep is less or equal zero
//           ippStsSizeErr     if roiSize.width <= 0 || roiSize.height <= 0
//           ippStsNoErr       else
//  Reference:
//      Jack Keith
//      Video Demystified: a handbook for the digital engineer, 2nd ed.
//      1996.pp.(40-41)
//
//     The YUV color space is the basic color space used by the PAL , NTSC , and
//  SECAM composite color video standarts.
//
//  The function ippiRGBToYUV422_ uses 4:2:2 sampling format.For every
//  two  horisontal Y samples, there is one U and V sample.
//
//  The function ippiRGBToYUV420_ uses 4:2:0 sampling format. 4:2:0 implements
//  2:1 reduction of U and V in both the vertical and horizontal directions.
//
//  The basic equations to convert between gamma-corrected RGB(R'G'B')and YUV are:
//
//       Y' =  0.299*R' + 0.587*G' + 0.114*B'
//       U  = -0.147*R' - 0.289*G' + 0.436*B' = 0.492*(B' - Y' )
//       V  =  0.615*R' - 0.515*G' - 0.100*B' = 0.877*(R' - Y' )
//
//       R' = Y' + 1.140 * V
//       G' = Y' - 0.394 * U - 0.581 * V
//       B' = Y' + 2.032 * U
//
//     For digital RGB values with the range [0 .. 255], Y has the range [0..255],
//   U the range [-112 .. +112],V the range [-157..+157].
//
//   These equations are usually scaled to simplify the implementation in an actual
//   NTSC or PAL digital encoder or decoder.
//
*/
IPPAPI(IppStatus, ippiRGBToYUV422_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRGBToYUV422_8u_C3P3R,(
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst[3],int dstStep[3], IppiSize roiSize))
IPPAPI(IppStatus, ippiRGBToYUV420_8u_C3P3R,(
                     const Ipp8u* pSrc, int srcStep ,
                           Ipp8u* pDst[3], int dstStep[3], IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV422ToRGB_8u_C3R,(
                     const Ipp8u* pSrc,int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV422ToRGB_8u_P3C3R,(
                     const Ipp8u* const pSrc[3],int srcStep[3],
                           Ipp8u* pDst,int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV420ToRGB_8u_P3C3R,(
                     const Ipp8u* const pSrc[3],int srcStep[3],
                           Ipp8u* pDst, int dstStep, IppiSize roiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiRGBToYUV422_8u_P3,   ippiYUV422ToRGB_8u_P3.
//              ippiRGBToYUV422_8u_C3P3, ippiYUV422ToRGB_8u_P3C3.
//              ippiRGBToYUV420_8u_C3P3, ippiYUV420ToRGB_8u_P3C3.
//              ippiRGBToYUV420_8u_P3,   ippiYUV420ToRGB_8u_P3.
//  Purpose:    Convert a RGB image to and from an YUV format image.
//  Arguments:
//     pSrc - Pointer to the source image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     pDst - Pointer to the resultant image (for pixel-order data).An array of pointers
//            to separate source color planes (in case of plane-order data)
//     roiSize - the size of image.
//  Returns:
//           ippStsNullPtrErr  if src == NULL or dst == NULL
//           ippStsStepErr,    if srcStep or dstStep is less or equal zero
//           ippStsSizeErr     if roiSize.width <= 0 || roiSize.height <= 0
//           ippStsNoErr       else
//  Reference:
//      Jack Keith
//      Video Demystified: a handbook for the digital engineer, 2nd ed.
//      1996.pp.(40-41)
//
//     The YUV color space is the basic color space used by the PAL , NTSC , and
//  SECAM composite color video standarts.
//
//  The function ippiRGBToYUV422_ uses 4:2:2 sampling format.For every
//  two  horisontal Y samples, there is one U and V sample.
//
//  The function ippiRGBToYUV420_ uses 4:2:0 sampling format. 4:2:0 implements
//  2:1 reduction of U and V in both the vertical and horizontal directions.
//
//  The basic equations to convert between gamma-corrected RGB(R'G'B')and YUV are:
//
//       Y' =  0.299*R' + 0.587*G' + 0.114*B'
//       U  = -0.147*R' - 0.289*G' + 0.436*B' = 0.492*(B' - Y' )
//       V  =  0.615*R' - 0.515*G' - 0.100*B' = 0.877*(R' - Y' )
//
//       R' = Y' + 1.140 * V
//       G' = Y' - 0.394 * U - 0.581 * V
//       B' = Y' + 2.032 * U
//
//   For digital RGB values with the range [0 .. 255], Y has the range [0..255],
//   U the range [-112 .. +112],V the range [-157..+157].
//
//   These equations are usually scaled to simplify the implementation in an actual
//   NTSC or PAL digital encoder or decoder.
//
*/
IPPAPI(IppStatus, ippiRGBToYUV422_8u_C3P3,(const Ipp8u* pSrc, Ipp8u* pDst[3], IppiSize roiSize))
IPPAPI(IppStatus, ippiRGBToYUV420_8u_C3P3,(const Ipp8u* pSrc, Ipp8u* pDst[3], IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV422ToRGB_8u_P3C3,(const Ipp8u* const pSrc[3],Ipp8u* pDst, IppiSize roiSize ))
IPPAPI(IppStatus, ippiYUV420ToRGB_8u_P3C3,(const Ipp8u* const pSrc[3], Ipp8u* pDst, IppiSize roiSize))

IPPAPI(IppStatus, ippiYUV420ToBGR565_8u16u_P3C3R,(const Ipp8u* const pSrc[3], int srcStep[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV420ToBGR555_8u16u_P3C3R,(const Ipp8u* const pSrc[3], int srcStep[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV420ToBGR444_8u16u_P3C3R,(const Ipp8u* const pSrc[3], int srcStep[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiYUV420ToRGB565_8u16u_P3C3R,(const Ipp8u* const pSrc[3], int srcStep[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV420ToRGB555_8u16u_P3C3R,(const Ipp8u* const pSrc[3], int srcStep[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiYUV420ToRGB444_8u16u_P3C3R,(const Ipp8u* const pSrc[3], int srcStep[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))

/* /////////////////////////////////////////////////////////////////////////////
//                  Geomentric Transforms Functions
///////////////////////////////////////////////////////////////////////////// */

#if !defined( _OWN_BLDPCS )
typedef enum {
    ippAxsHorizontal,
    ippAxsVertical,
    ippAxsBoth
} IppiAxis;


enum {
    IPPI_INTER_NN     = 1,
    IPPI_INTER_LINEAR = 2,
    IPPI_INTER_CUBIC  = 4,
    IPPI_INTER_SUPER  = 8,
    IPPI_SMOOTH_EDGE  = (1 << 30)
};

typedef enum {
    dirWarpRtoQ  = 0,
    dirWarpQtoR  = 1
} IppiWarpDirection;

#endif /* _OWN_BLDPCS */

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippiMirror
//
// Purpose:    Mirrors the sourse image about a horizontal
//             or vertical or both together axes into resultant image
//
//
// Arguments:
//    pSrc        pointer to the source image ROI
//    srcStep     scan line size (bytes) of the source image
//    pDst        pointer to the target image ROI
//    dstStep     scan line size (bytes) of the source image
//    roiSize     ROI size
//    flip        specifies the axes to mirror the image:
//                   ippAxsHorizontal  for the horizontal axis,
//                   ippAxsVertical    for a vertical axis,
//                   ippAxsBoth        for both horizontal and vertical axes
//
// Returns:                Reason:
//    ippStsNoErr          no problems
//    ippStsNullPtrErr     NULL pointer
//    ippStsStepErr        srcStep<=0 or dstStep<=0
//    ippStsSizeErr        ROI size error
//    ippStsMirrorFlipErr  unknown flip value
*/
IPPAPI(IppStatus, ippiMirror_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize,
                     IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep, IppiSize roiSize,
                     IppiAxis flip))



/* ////////////////////////////////////////////////////////////////////////// */
/*                   Threshold operations                                     */
/* ////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_GT_8u_C1R
//              ippiThreshold_GT_8u_C3R
//
//  Purpose:        Threshold operation if Greater
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Some of pointers to pSrc or pDst are NULL
//   ippStsSizeErr     Some size of roi less or equal zero
//
//  Parameters:
//   pSrc       pointer to input image
//   srcStep    size of input image scan-line
//   pDst       pointer to output image
//   dstStep    size of output image scan-line
//   roiSize    ROI size
//   threshold  level (or levels) of the threshold operation
*/
IPPAPI(IppStatus,ippiThreshold_GT_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold))
IPPAPI(IppStatus,ippiThreshold_GT_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3]))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_LT_8u_C1R
//              ippiThreshold_LT_8u_C3R
//
//  Purpose:        Threshold operation if Less
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Some of pointers to pSrc or pDst are NULL
//   ippStsSizeErr     Some size of roi less or equal zero
//
//  Parameters:
//   pSrc       pointer to input image
//   srcStep    size of input image scan-line
//   pDst       pointer to output image
//   dstStep    size of output image scan-line
//   roiSize    ROI size
//   threshold  level (or levels) of the threshold operation
*/
IPPAPI(IppStatus,ippiThreshold_LT_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold))
IPPAPI(IppStatus,ippiThreshold_LT_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3]))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_GTVal_8u_C1R
//              ippiThreshold_GTVal_8u_C3R
//
//  Purpose:        Thresold operations. Replace if Greater.
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Some of pointers to pSrc or pDst are NULL
//   ippStsSizeErr     Some size of roi less or equal zero
//
//  Parameters:
//   pSrc       pointer to input image
//   srcStep    size of input image scan-line
//   pDst       pointer to output image
//   dstStep    size of output image scan-line
//   roiSize    ROI size
//   threshold  level (or levels) of the threshold operation
//   value      replacing value (or values)
//   ippCmpOp   comparison mode, ippCmpLess or ippCmpGreater
*/
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold,
       Ipp8u value))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3]))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_LTVal_8u_C1R
//              ippiThreshold_LTVal_8u_C3R
//
//  Purpose:        Thresold operations. Replace if Less.
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Some of pointers to pSrc or pDst are NULL
//   ippStsSizeErr     Some size of roi less or equal zero
//
//  Parameters:
//   pSrc       pointer to input image
//   srcStep    size of input image scan-line
//   pDst       pointer to output image
//   dstStep    size of output image scan-line
//   roiSize    ROI size
//   threshold  level (or levels) of the threshold operation
//   value      replacing value (or values)
//   ippCmpOp   comparison mode, ippCmpLess or ippCmpGreater
*/
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold,
       Ipp8u value))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3]))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_LTValGTVal_8u_C1R
//              ippiThreshold_LTValGTVal_8u_C3R
//
//  Purpose:        Threshold operation
//  Return:
//   ippStsNoErr                Ok
//   ippStsNullPtrErr           Some of pointers to pSrc or pDst are NULL
//   ippStsSizeErr              Some size of roi less or equal zero
//   ippStsThreshErr            if (thresholdGT[n] < thresholdLT[n])
//
//  Parameters:
//   pSrc           pointer to input image
//   srcStep        size of input image scan-line
//   pDst           pointer to output image
//   dstStep        size of output image scan-line
//   pSrcDst        pointer to input for in-place operation
//   srcDstStep     size of image scan-line for in-place operation
//   roiSize        ROI size
//   thresholdGT    level (or levels) of the threshold operation Greater
//   valueGT        replacing value (or values) of the threshold operation
//                  Greater
//   thresholdLT    level (or levels) of the threshold operation Less
//   valueLT        replacing value (or values) of the threshold operation
//                  Less
*/
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_C1R,(const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize,
       Ipp8u thresholdLT, Ipp8u valueLT,
       Ipp8u thresholdGT, Ipp8u valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_C3R,(const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize,
       const Ipp8u thresholdLT[3], const Ipp8u valueLT[3],
       const Ipp8u thresholdGT[3], const Ipp8u valueGT[3]))



/* /////////////////////////////////////////////////////////////////////////////
//                  Statistic Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                   Norm Functions
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
// Names:       ippiNorm_Inf_8u_C1RSfs
//              ippiNorm_Inf_8u_C3RSfs
//              ippiNorm_L1_8u_C1RSfs
//              ippiNorm_L1_8u_C3RSfs
//              ippiNorm_L2_8u_C1RSfs
//              ippiNorm_L2_8u_C3RSfs
//
//              ippiNormDiff_Inf_8u_C1RSfs
//              ippiNormDiff_Inf_8u_C3RSfs
//              ippiNormDiff_L1_8u_C1RSfs
//              ippiNormDiff_L1_8u_C3RSfs
//              ippiNormDiff_L2_8u_C1RSfs
//              ippiNormDiff_L2_8u_C3RSfs
//
//              ippiNormRel_Inf_8u_C1RSfs
//              ippiNormRel_Inf_8u_C3RSfs
//              ippiNormRel_L1_8u_C1RSfs
//              ippiNormRel_L1_8u_C3RSfs
//              ippiNormRel_L2_8u_C1RSfs
//              ippiNormRel_L2_8u_C3RSfs
//
// Purpose: ROI-oriented statistical norm functions.
//
// Arguments:
//    pSrc        pointers to the images ROI
//    srcStep     sizes of image scanline, in bytes
//    roiSize     ROI size
//    pNorm       pointer to resulting value (1-channel images)
//    norm[3]     address of resulting values vector (3-channel images)
//    scaleFactor scale factor value.  Resulting values are multiplied
//                by (2^(-scaleFactor))
//
// Returns:                Reason:
//    ippStsNullPtrErr        NULL pointer
//    ippStsSizeErr           illegal ROI size
//    ippStsDivByZeroErr      the norm of the second image == 0 (for relative only)
//    ippStsNoErr             no error
*/
IPPAPI (IppStatus, ippiNorm_Inf_8u_C1RSfs,(
                     const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))
IPPAPI (IppStatus, ippiNorm_L1_8u_C1RSfs, (
                     const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))
IPPAPI (IppStatus, ippiNorm_L2_8u_C1RSfs, (
                     const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))

IPPAPI (IppStatus, ippiNorm_Inf_8u_C3RSfs,(
                     const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))
IPPAPI (IppStatus, ippiNorm_L1_8u_C3RSfs, (
                     const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))
IPPAPI (IppStatus, ippiNorm_L2_8u_C3RSfs, (
                     const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))

IPPAPI (IppStatus, ippiNormDiff_Inf_8u_C1RSfs,(
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))
IPPAPI (IppStatus, ippiNormDiff_L1_8u_C1RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))
IPPAPI (IppStatus, ippiNormDiff_L2_8u_C1RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))

IPPAPI (IppStatus, ippiNormDiff_Inf_8u_C3RSfs,(
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))
IPPAPI (IppStatus, ippiNormDiff_L1_8u_C3RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))
IPPAPI (IppStatus, ippiNormDiff_L2_8u_C3RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))

IPPAPI (IppStatus, ippiNormRel_Inf_8u_C1RSfs,(
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))
IPPAPI (IppStatus, ippiNormRel_L1_8u_C1RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))
IPPAPI (IppStatus, ippiNormRel_L2_8u_C1RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s* pNorm, int scaleFactor))

IPPAPI (IppStatus, ippiNormRel_Inf_8u_C3RSfs,(
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))
IPPAPI (IppStatus, ippiNormRel_L1_8u_C3RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))
IPPAPI (IppStatus, ippiNormRel_L2_8u_C3RSfs, (
                     const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step, IppiSize roiSize,
                     Ipp32s norm[3], int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//                   Moment Functions
///////////////////////////////////////////////////////////////////////////// */
#if !defined( _OWN_BLDPCS )
    struct MomentState64s;
    typedef struct MomentState64s IppiMomentState_64s;
    typedef Ipp64s IppiHuMoment_64s[7];
    typedef Ipp64f IppiHuMoment_64f[7];
#endif /* _OWN_BLDPCS */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMomenGetStateSize()
//             ippiMomentInit()
//             ippiMomentInitAlloc()
//
//  Purpose:   Moment State Init
//
//  Parameters:
//    hint     utilized kind of code hint
//    pState   to be initializing pointer to the Moment State
//
//  Return:             Reason:
//    ippStsNoErr       no problem
//    ippStsNullPtrErr  NULL pointer
//    ippStsMemAllocErr memory allocation pronlem has occured
*/
IPPAPI(IppStatus, ippiMomentGetStateSize_64s, (IppHintAlgorithm hint, int* pSize))
IPPAPI(IppStatus, ippiMomentInit_64s,      (IppiMomentState_64s*  pState, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippiMomentInitAlloc_64s, (IppiMomentState_64s** pState, IppHintAlgorithm hint))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMomentFree()
//
//  Purpose:   Remove Moment State
//
//  Parameters:
//    pState   pointer to the Moment State
//
//  Return:                   Reason:
//    ippStsNoErr             no problem - context was created/removed
//    ippStsContextMatchErr   mismatch context ID
//
*/
IPPAPI (IppStatus, ippiMomentFree_64s, (IppiMomentState_64s* pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMoments
//
//  Purpose:   Calculate Statistical Moments
//
//  Returns:
//    ippStsContextMatchErr   pState->idCtx != idCtxMoment
//    ippStsNullPtrErr        (pSrc == NULL) or (pState == NULL)
//    ippStsStepErr           pSrcStep <0
//    ippStsSizeErr           (roiSize.width  <1) or (roiSize.height <1)
//    ippStsNoErr             no errors
//
//  Parameters:
//    pSrc     pointer to the image ROI
//    srcStep  size of image scan-line
//    roiSize  size of ROI
//    pState   pointer to the Moment State
//
//  Notes:
//    We only consider moments up to the 3-rd order
//
*/
IPPAPI(IppStatus,ippiMoments64s_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))
IPPAPI(IppStatus,ippiMoments64s_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiGetSpatialMoment()
//             ippiGetCentralMoment()
//
//  Purpose:   Read out Spatial/Central Moment Value
//
//  Returns:
//    ippStsNullPtrErr        (pState == NULL) or (pValue == NULL)
//    ippStsContextMatchErr   pState->idCtx != idCtxMoment
//    ippStsSizeErr           mOrd>3 or nOrd>3 or (mOrd+nOrd)>3
//    ippStsChannelErr        illegal channel number
//    ippStsNoErr             if no errors
//
//  Parameters:
//    pState   pointer to the Moment State
//    mOrd     m- Order (X direction)
//    nOrd     n- Order (Y direction)
//    nChannel Channel Number
//    roiOffset ROI location (ippiGetSpatialMoment ONLY!)
//    pValue   pointer to the moment value
//
//  NOTE:
//    ippiGetSpatialMoment use Absolute Coordinates (left-top image has 0,0).
//
*/
IPPAPI(IppStatus,ippiGetSpatialMoment_64s,(const IppiMomentState_64s* pState,
                                       int mOrd, int nOrd, int nChannel,
                                       IppiPoint roiOffset, Ipp64s* value, int scaleFactor))
IPPAPI(IppStatus,ippiGetCentralMoment_64s,(const IppiMomentState_64s* pState,
                                       int mOrd, int nOrd, int nChannel,
                                       Ipp64s* value, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiGetNormalizedSpatialMoment()
//             ippiGetNormalizedCentralMoment()
//
//  Purpose:   Read out Normalized Spatial/Central Moment Value.
//
//  Returns:
//    ippStsNullPtrErr        (pState == NULL) or (pValue == NULL)
//    ippStsContextMatchErr   pState->idCtx != idCtxMoment
//    ippStsSizeErr           mOrd>3 or nOrd>3 or (mOrd+nOrd)>3
//    ippStsChannelErr        illegal channel number
//    ippStsMoment00ZeroErr   mm[0][0] < IPP_EPS52
//    ippStsNoErr             if no errors
//
//  Parameters:
//    pState   pointer to the Moment State
//    mOrd     m- Order (X direction)
//    nOrd     n- Order (Y direction)
//    nChannel Channel Number
//    roiOffset ROI location (ippiGetNormalizedSpatialMoment ONLY!)
//    pValue   pointer to the moment value
//
*/
IPPAPI(IppStatus,ippiGetNormalizedSpatialMoment_64s,(const IppiMomentState_64s* pState,
                                   int mOrd, int nOrd, int nChannel,
                                   IppiPoint roiOffset, Ipp64s* value, int scaleFactor))
IPPAPI(IppStatus,ippiGetNormalizedCentralMoment_64s,(const IppiMomentState_64s* pState,
                                   int mOrd, int nOrd, int nChannel,
                                   Ipp64s* value, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiGetHuMoments()
//
//  Purpose:   Calculates Hu Moments.
//
//  Returns:
//    ippStsNullPtrErr      (pState == NULL) or (pHu == NULL)
//    ippStsContextMatchErr pState->idCtx != idCtxMoment
//    ippStsSizeErr         (nChannel<0) or (nChannel>=pState->nChannelInUse)
//    ippStsMoment00ZeroErr mm[0][0] < IPP_EPS52
//    ippStsNoErr           if no errors
//
//  Parameters:
//    pState   pointer to the Moment State
//    nChannel Channel Number
//    pHu      pointer to the array of Hu moments
//
//  Notes:
//    We only consider Hu moments up to the 7-th order
*/
IPPAPI(IppStatus,ippiGetHuMoments_64s,(const IppiMomentState_64s* pState,
                                   int nChannel, IppiHuMoment_64s pHm, int scaleFactor))



/* /////////////////////////////////////////////////////////////////////////////
//                  Morphological Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippiErode   ippiDilate
//
// Purpose:    Perform Morphology Operation ERODE (DILATE)
//             of image ROI
//
// Arguments:
//    pSrc     pointer to the source image
//    srcStep  source image scanline
//    pDst     pointer to the target image
//    srcStep  target image scanline
//    roiSize  ROI size
//
//  Returns:            Reason:
//    ippStsNullPtrErr  NULL pointer
//    ippStsStepErr     illegal step value
//    ippStsSizeErr     illegal ROI size
//    ippStsNoErr       no errors
*/

IPPAPI(IppStatus,ippiErode3x3_8u_C1R, (
                     const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiErode3x3_8u_C3R, (
                     const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus,ippiDilate3x3_8u_C1R,(
                     const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiDilate3x3_8u_C3R,(
                     const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize))


#ifdef __cplusplus
}
#endif

#endif /* __IPPIP_H__ */
/* ////////////////////////// End of file "ippIP.h" ////////////////////////// */
