/* $Id$ */

/*
 * Copyright (c) 2003 AGAWA Koji <kaoru-k @self-core.org="">
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software withough specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file w100api_fake.h
 * @brief 
 *
 * 
 *
 * @author AGAWA Koji
 * @date $Date$
 * @version $Revision$
 */

#include <sys/types.h>

#ifndef W100API_FAKE_H_INCLUDED
#define W100API_FAKE_H_INCLUDED

#ifdef __cplusplus
# define EXTERN_C_BEGIN extern "C" {
# define EXTERN_C_END }
#else
# define EXTERN_C_BEGIN
# define EXTERN_C_END
#endif

EXTERN_C_BEGIN

// DP_GUI_MASTER_CNTL.GMC_Dst_DataType
// DP_DATATYPE.Dp_Dst_DataType
// w100fb.h ���ͤȤϰ㤦��
/* #define DSTTYPE_8BPP            2       // 8 bpp grey scale */
/* #define DSTTYPE_16BPP_1555      3       //16 bpp aRGB 1555 */
/* #define DSTTYPE_16BPP_444       5       //16 bpp aRGB 4444 */
#define DSTTYPE_8BPP            1

// DP_GUI_MASTER_CNTL.GMC_Src_DataType
// DP_DATATYPE.Dp_Src_DataType
// w100fb.h ��ꡣ¿ʬ���äƤ�Ȼפ���
#define SRCTYPE_1BPP_OPA        0       //mono (expanded to frgd, bkgd)
#define SRCTYPE_1BPP_TRA        1       //mono (expanded to frgd, leave_alone)
#define SRCTYPE_EQU_DST         3       //color (same as DST)
#define SRCTYPE_SOLID_COLOR_BLT 4       //solid color for Blt (use frgd)
#define SRCTYPE_4BPP            5       //4 bpp
#define SRCTYPE_12BPP_PACKED    6       //12 bpp packed

#define ROP3_SRCCOPY            0xCC

#define OVLTYPE_YUV420          7
#define OVLTYPE_RGB565          8

typedef struct {
    /* ����ȷ���̤���� */
    int16_t XCoord;
    int16_t YCoord;
} ATI_POINT;

typedef struct {
    /* ����ȷ���̤���� */
    int16_t XCoord;
    int16_t YCoord;
    int16_t Width;
    int16_t Height;
} ATI_RECT;

typedef struct {
    int16_t X_Top_Left;                  // x coordinate of top left corner
    int16_t Y_Top_Left;                  // y coordinate of top left corner
    int16_t X_Bottom_Right;              // x coordinate of bottom right corner
    int16_t Y_Bottom_Right;              // y coordinate of bottom right corner
} ATI_CLIPRECT;

typedef struct {
    /* ����ȷ���̤���� */
    uint32_t Count;                        /* +0 ���֤� */
    uint8_t ScaleXFactor;                 /* +4 ����(16=���ܡ�) */
    uint8_t ScaleYFactor;                 /* +5 ���� */
    uint8_t BlendOn;                      /* +6 ���� */
    uint8_t dummy1;                       /* ̤���ѡ� */
} ATI_STRETCH;                          /* 8bytes? */

typedef struct {
    uint32_t *lpSrcBitmap;                /* �����ե����Υ��ե��å� */
    uint16_t XCoord;                      /* +4  ����:�����ե������x��ɸ */
    uint16_t YCoord;                      /* +6  ����:�����ե������y��ɸ */
    uint16_t SrcPitch;                    /* +8  ����: */
    uint16_t SrcHeight;                   /* +10 ����: */
    uint16_t OverlayWidth;                /* �����Х쥤����(Src�Ȱ㤦�ͤˤ��Ƥ⡢ưŪ�˳���̾����줿��Ϥ��ʤ�����̣����Ρ�) */
    uint16_t OverlayHeight;
    uint32_t lpOverlayKey;                /* +16 ����:��(���顼������) */
    uint8_t OverlayFormat;               /* +20 ���� */
    uint8_t dummy1;
    uint16_t dummy2;
} ATI_OVERLAYPROP;                      /* 24bytes? */

typedef struct {
    int HInvert;
    int VInvert;
} ATI_EXTVIDEOPROP;

typedef struct {
    ATI_EXTVIDEOPROP ExtVideoProp;
} ATI_UNKNOWN1;

typedef struct {
    uint32_t dummy1;
    uint32_t dummy2;
    uint8_t HExpansion;                   /* +8  ���� */
    uint8_t VExpansion;                   /* +9  ���� */
    uint8_t dummy3;
    uint8_t dummy4;
    uint8_t RConversion;                  /* +12 ���� */
    uint8_t dummy5;
    uint8_t dummy6;
    uint8_t dummy7;
    ATI_UNKNOWN1 x;
} ATI_EXTENDEDOVERLAYPROP;              /* 16byte? */

/**
 * API�����Ѥ򳫻Ϥ��롣
 *
 * @return              1:success, 0:fail
 */
int AtiCore_ProcessAttach(void);

/**
 * API�����Ѥ�λ���롣
 *
 * @return              *����*
 */
int AtiCore_ProcessDetach(void);

/**
 * �����ե�����ӥǥ������˺������롣
 * TODO: ExtRam �˳��ݤ�����ˡ�ϡ�
 *
 * @arg     handle      (����)�����ե����Υϥ�ɥ�
 * @arg     offset      (����)�����ե����Υ��ե��å�
 * @arg     size        �����ե����Υ�����(bytes)
 * @arg     direction   (0:��̤����̤�, 1:��̤�����̤�)�����äƳ���
 * @return              1:success, 0:fail
 */
int AtiCore_AllocateSurface(uint16_t *handle, uint32_t *offset,
                            uint32_t size, uint32_t direction);

/**
 * �����ե������˴����롣
 *
 * @arg     handle      �����ե����Υϥ�ɥ�
 * @return              1:success, 0:fail
 */
int AtiCore_DestroySurface(uint16_t handle);

/**
 * BitBlt �ϴؿ��� ROP(�饹�������ڥ졼�����) �����ꤹ�롩
 *
 * @param   rop         8�ӥåȤΥե饰�Ȼפ���
 */
int AtiCore_SetRopOperation(uint32_t rop);

/**
 * BitBlt �ϴؿ��ǻȤ��륵���ե����Υԥ�����ե����ޥåȤ����ꤹ�롩
 *
 */
int AtiCore_SetDstType(uint32_t);
int AtiCore_SetSrcType(uint32_t);

/**
 * BitBlt �ϴؿ��Υ���åԥ󥰤����ꡩ
 *
 */
int AtiCore_SetSrcClippingRect(ATI_CLIPRECT *cliprect);
int AtiCore_SetDstClippingRect(ATI_CLIPRECT *cliprect);

/**
 * BitBlt �ϴؿ��ǻȤ��륵���ե����Υԥå��ȥ��ե��åȤ����ꤹ�롣
 */
int AtiCore_SetSrcPitchOffset(int pitch, int offset);
int AtiCore_SetDstPitchOffset(int pitch, int offset);

/**
 * �ޤ���
 */
int AtiCore_BitBltFilpRotate(int flags,
                             ATI_RECT *dstRect, ATI_RECT *srcRect);

/**
 * �ޤ���
 */
int AtiCore_StretchBlt(ATI_STRETCH *option,
                       ATI_POINT *point, ATI_RECT *srcRect);


/**
 * (BitBlt�ʤɤ�)��������λ����Τ��Ԥġ�
 *
 * @param   nsec        �������Ȼ���(msec)
 * @return              1:��������λ����, 0:�����Ϥޤ�����äƤ��ʤ�
 */
int AtiCore_WaitComplete(int msec);

/**
 * �����Х쥤����ݤ��롣
 *
 * AtiCore_SetOverlayOnOff(handle, true) ���ʤ��ȡ������Х쥤�����ե�����
 * ɽ������ʤ���
 *
 * @param   handle      (����)�����Х쥤�Υϥ�ɥ�
 * @return              1:success, 0:fail
 */
int AtiCore_AllocOverlay(uint16_t *handle);

/**
 * �����Х쥤��������롣
 *
 * AtiCore_SetOverlayOnOff(handle, false) ���ʤ��ȡ������Х쥤�����ե�����
 * ɽ�����줿�ޤޤˤʤ롣
 *
 * @param   handle      �����Х쥤�Υϥ�ɥ�
 */
int AtiCore_ReleaseOverlay(uint16_t handle);

/**
 * �����Х쥤������򤹤롣
 *
 * @return              1:success, 0:fail
 */
int AtiCore_SetupOverlay(uint16_t handle, ATI_OVERLAYPROP *prop);

/**
 * �����Х쥤�γ�ĥ����򤹤롣
 *
 */
int AtiCore_SetupOverlayExtended(uint16_t handle, ATI_EXTENDEDOVERLAYPROP *prop);

/**
 * �����Х쥤�����ե�����ɽ��/��ɽ�������ꤹ�롣
 *
 * @param   handle      �����Х쥤�Υϥ�ɥ�
 * @param   isShow      1:ɽ��, 0:��ɽ��
 * @return              1:success, 0:fail
 */
int AtiCore_SetOverlayOnOff(uint16_t handle, int isShow);

/**
 * �����Х쥤�����ե�����ɽ�����֤����ꤹ�롣
 *
 * @param   handle      �����Х쥤�Υϥ�ɥ�
 * @param   x           x ��ɸ
 * @param   y           y ��ɸ
 */
int AtiCore_SetOverlayPos(uint16_t handle, uint16_t x, uint16_t y);

/**
 * VRAM ���Ф���ľ���ꥢ�������򳫻Ϥ��롣
 *
 * @param   offset      �����ե����Υ��ե��å�
 * @param   regdata     (����)offset ���б����륢�ɥ쥹
 */
int AtiCore_SetupMemoryTransfer(uint32_t offset, uint32_t *regdata);

/**
 * VRAM ���Ф���ľ���ꥢ��������λ���롣
 */
int AtiCore_TerminateMemoryTransfer(void);

/**
 * �ե��ȥХåե��Υԥå��ȥ��ե��åȤ�������롣
 *
 * @param   pitch       (����)�����ե����Υԥå�
 * @param   offset      (����)�����ե����Υ��ե��å�
 */
int AtiCore_GetFrontBufferPitchOffset(uint32_t *pitch, uint32_t *offset);

/**
 * ���뤵���ѹ���(�����Х쥤�Τߡ�)
 *
 * @param   brightness  (��)-64...63(��)
 * @return              1:success, 0:fail
 */
int AtiCore_SetDisplayBrightness(int brightness);

/**
 * ��������Ƥ���ӥǥ�����Υ�������������롣
 *
 * @param   internal    (����)����VRAM������(�Х���)
 * @param   external    (����)����VRAM������(�Х���)
 * @return              1:success, 0:fail
 */
int GetAvailableVideoMem(uint32_t *internal, uint32_t *external);

/* ================================================================ */
/* from libqte.so.2.3.2 */
/*
AtiCore_AlphaBlend
AtiCore_BitBlt(int, ATIRect*, ATIRect*)?
AtiCore_BrushType
AtiCore_CursorOnOff
AtiCore_DrawPixel
AtiCore_Flush
AtiCore_GammaCorrection
AtiCore_GetCRC
AtiCore_GetCursorPos
AtiCore_GetDeviceInfo
AtiCore_GetGPIO_Data
AtiCore_GetGraphicExtended
AtiCore_GetGraphicWindowPos
AtiCore_GetLargestVideoMemBlock
AtiCore_GetLastError
AtiCore_GetMultiCRC
AtiCore_GetOverlayPos
AtiCore_GetPitchOffsetProperty
AtiCore_Host
AtiCore_LoadCursorBitMap
AtiCore_PaintRect
AtiCore_PolyScanline
AtiCore_Polyline
AtiCore_ProcessAttachMinimal(void)?
AtiCore_ProcessAttachSpecialMode
AtiCore_ProcessDetachMinimal(void)?
AtiCore_ProcessDetachSpecialMode
AtiCore_ReadCfgReg
AtiCore_ReadMem(int, int)?
AtiCore_ReadReg(int, int)?
AtiCore_ScanlineShading
AtiCore_SetApertures
AtiCore_SetBkgColour
AtiCore_SetBytePixelOrder
AtiCore_SetCursorPos
AtiCore_SetDisplayParameters
AtiCore_SetDriverBehaviour
AtiCore_SetFrgColour
AtiCore_SetFrontBuffer(int, int, int)?
AtiCore_SetGPIO_Data
AtiCore_SetGraphicWindowOnOff
AtiCore_SetGraphicWindowPos
AtiCore_SetOverlayPosUsingGraphicWindowXY
AtiCore_SetPartialCursor
AtiCore_SetupGraphicExtended
AtiCore_SetupGraphicWindow(int)?
AtiCore_SetupPM4
AtiCore_SmallText
AtiCore_SubmitPM4Packet
AtiCore_TransBitBlt
AtiCore_WriteCfgReg
AtiCore_WriteMem
AtiCore_WriteReg
 */

EXTERN_C_END

#endif /* W100API_FAKE_H_INCLUDED */
