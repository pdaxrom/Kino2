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
// w100fb.h の値とは違う。
/* #define DSTTYPE_8BPP            2       // 8 bpp grey scale */
/* #define DSTTYPE_16BPP_1555      3       //16 bpp aRGB 1555 */
/* #define DSTTYPE_16BPP_444       5       //16 bpp aRGB 4444 */
#define DSTTYPE_8BPP            1

// DP_GUI_MASTER_CNTL.GMC_Src_DataType
// DP_DATATYPE.Dp_Src_DataType
// w100fb.h より。多分あってると思う。
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
    /* 順序と型が未確定 */
    int16_t XCoord;
    int16_t YCoord;
} ATI_POINT;

typedef struct {
    /* 順序と型が未確定 */
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
    /* 順序と型が未確定 */
    uint32_t Count;                        /* +0 たぶん */
    uint8_t ScaleXFactor;                 /* +4 確定(16=等倍？) */
    uint8_t ScaleYFactor;                 /* +5 確定 */
    uint8_t BlendOn;                      /* +6 確定 */
    uint8_t dummy1;                       /* 未使用？ */
} ATI_STRETCH;                          /* 8bytes? */

typedef struct {
    uint32_t *lpSrcBitmap;                /* サーフェスのオフセット */
    uint16_t XCoord;                      /* +4  確定:サーフェス内のx座標 */
    uint16_t YCoord;                      /* +6  確定:サーフェス内のy座標 */
    uint16_t SrcPitch;                    /* +8  確定: */
    uint16_t SrcHeight;                   /* +10 確定: */
    uint16_t OverlayWidth;                /* オーバレイの幅(Srcと違う値にしても、動的に拡大縮小されたりはしない、意味あんの？) */
    uint16_t OverlayHeight;
    uint32_t lpOverlayKey;                /* +16 確定:謎(カラーキー？) */
    uint8_t OverlayFormat;               /* +20 確定 */
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
    uint8_t HExpansion;                   /* +8  確定 */
    uint8_t VExpansion;                   /* +9  確定 */
    uint8_t dummy3;
    uint8_t dummy4;
    uint8_t RConversion;                  /* +12 確定 */
    uint8_t dummy5;
    uint8_t dummy6;
    uint8_t dummy7;
    ATI_UNKNOWN1 x;
} ATI_EXTENDEDOVERLAYPROP;              /* 16byte? */

/**
 * APIの利用を開始する。
 *
 * @return              1:success, 0:fail
 */
int AtiCore_ProcessAttach(void);

/**
 * APIの利用を終了する。
 *
 * @return              *不明*
 */
int AtiCore_ProcessDetach(void);

/**
 * サーフェスをビデオメモリ上に作成する。
 * TODO: ExtRam に確保する方法は？
 *
 * @arg     handle      (返値)サーフェスのハンドル
 * @arg     offset      (返値)サーフェスのオフセット
 * @arg     size        サーフェスのサイズ(bytes)
 * @arg     direction   (0:低位から高位へ, 1:高位から低位へ)向かって確保
 * @return              1:success, 0:fail
 */
int AtiCore_AllocateSurface(uint16_t *handle, uint32_t *offset,
                            uint32_t size, uint32_t direction);

/**
 * サーフェスを破棄する。
 *
 * @arg     handle      サーフェスのハンドル
 * @return              1:success, 0:fail
 */
int AtiCore_DestroySurface(uint16_t handle);

/**
 * BitBlt 系関数の ROP(ラスターオペレーション) を設定する？
 *
 * @param   rop         8ビットのフラグと思われる
 */
int AtiCore_SetRopOperation(uint32_t rop);

/**
 * BitBlt 系関数で使われるサーフェスのピクセルフォーマットを設定する？
 *
 */
int AtiCore_SetDstType(uint32_t);
int AtiCore_SetSrcType(uint32_t);

/**
 * BitBlt 系関数のクリッピングの設定？
 *
 */
int AtiCore_SetSrcClippingRect(ATI_CLIPRECT *cliprect);
int AtiCore_SetDstClippingRect(ATI_CLIPRECT *cliprect);

/**
 * BitBlt 系関数で使われるサーフェスのピッチとオフセットを設定する。
 */
int AtiCore_SetSrcPitchOffset(int pitch, int offset);
int AtiCore_SetDstPitchOffset(int pitch, int offset);

/**
 * まだ謎
 */
int AtiCore_BitBltFilpRotate(int flags,
                             ATI_RECT *dstRect, ATI_RECT *srcRect);

/**
 * まだ謎
 */
int AtiCore_StretchBlt(ATI_STRETCH *option,
                       ATI_POINT *point, ATI_RECT *srcRect);


/**
 * (BitBltなどの)処理が完了するのを待つ？
 *
 * @param   nsec        ウェイト時間(msec)
 * @return              1:処理が完了した, 0:処理はまだ終わっていない
 */
int AtiCore_WaitComplete(int msec);

/**
 * オーバレイを確保する。
 *
 * AtiCore_SetOverlayOnOff(handle, true) しないと、オーバレイサーフェスは
 * 表示されない。
 *
 * @param   handle      (返値)オーバレイのハンドル
 * @return              1:success, 0:fail
 */
int AtiCore_AllocOverlay(uint16_t *handle);

/**
 * オーバレイを解放する。
 *
 * AtiCore_SetOverlayOnOff(handle, false) しないと、オーバレイサーフェスは
 * 表示されたままになる。
 *
 * @param   handle      オーバレイのハンドル
 */
int AtiCore_ReleaseOverlay(uint16_t handle);

/**
 * オーバレイの設定をする。
 *
 * @return              1:success, 0:fail
 */
int AtiCore_SetupOverlay(uint16_t handle, ATI_OVERLAYPROP *prop);

/**
 * オーバレイの拡張設定をする。
 *
 */
int AtiCore_SetupOverlayExtended(uint16_t handle, ATI_EXTENDEDOVERLAYPROP *prop);

/**
 * オーバレイサーフェスの表示/非表示を設定する。
 *
 * @param   handle      オーバレイのハンドル
 * @param   isShow      1:表示, 0:非表示
 * @return              1:success, 0:fail
 */
int AtiCore_SetOverlayOnOff(uint16_t handle, int isShow);

/**
 * オーバレイサーフェスの表示位置を設定する。
 *
 * @param   handle      オーバレイのハンドル
 * @param   x           x 座標
 * @param   y           y 座標
 */
int AtiCore_SetOverlayPos(uint16_t handle, uint16_t x, uint16_t y);

/**
 * VRAM に対する直メモリアクセスを開始する。
 *
 * @param   offset      サーフェスのオフセット
 * @param   regdata     (返値)offset に対応するアドレス
 */
int AtiCore_SetupMemoryTransfer(uint32_t offset, uint32_t *regdata);

/**
 * VRAM に対する直メモリアクセスを終了する。
 */
int AtiCore_TerminateMemoryTransfer(void);

/**
 * フロントバッファのピッチとオフセットを取得する。
 *
 * @param   pitch       (返値)サーフェスのピッチ
 * @param   offset      (返値)サーフェスのオフセット
 */
int AtiCore_GetFrontBufferPitchOffset(uint32_t *pitch, uint32_t *offset);

/**
 * 明るさの変更。(オーバレイのみ？)
 *
 * @param   brightness  (暗)-64...63(明)
 * @return              1:success, 0:fail
 */
int AtiCore_SetDisplayBrightness(int brightness);

/**
 * 実装されているビデオメモリのサイズを取得する。
 *
 * @param   internal    (返値)内部VRAMの容量(バイト)
 * @param   external    (返値)外部VRAMの容量(バイト)
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
