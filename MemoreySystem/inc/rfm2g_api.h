/*
===============================================================================
                            COPYRIGHT NOTICE

    Copyright (C) 2001, 2006, 2008, GE Fanuc Intelligent Platforms, Inc.
    International Copyright Secured.  All Rights Reserved.

-------------------------------------------------------------------------------

$Workfile: rfm2g_api.h $
$Revision: 43 $
$Modtime: 7/24/08 9:24a $

-------------------------------------------------------------------------------
    Description: RFM2G API Library Function Definitions
-------------------------------------------------------------------------------

==============================================================================*/

#ifndef __RFM2G_API_H
#define __RFM2G_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*

  The rfm2g_osspec.h header file should

  1) define STDRFM2GCALL which is used for functions that return RFM2G_STATUS
  2) define RFM2GHANDLE
  3) prototypes for driver specific functions
  4) include other header files as necessary.
  5) include common API definitions header file rfm2g_defs.h
  6) Include header file that defines RFM2G types, rfm2g_types.h

 */
#include "rfm2g_osspec.h"

/*****************************************************************************/
/*
    This header file defines the common PCI RFM2g API function call prototypes.
*/

/* RFM2G_EVENT_FUNCPTR is the type of user function called upon an interrupt if one is
   connected by calling RFM2gEnableEventCallback().  */
typedef void (*RFM2G_EVENT_FUNCPTR) (RFM2GHANDLE, RFM2GEVENTINFO*);

/*****************************************************************************/

/* File Open/Close */

STDRFM2GCALL RFM2gOpen(char *DevicePath, RFM2GHANDLE *rh);
STDRFM2GCALL RFM2gClose(RFM2GHANDLE *rh);


/*****************************************************************************/

/* Configuration */

STDRFM2GCALL RFM2gGetConfig(RFM2GHANDLE rh, RFM2GCONFIG *Config);

STDRFM2GCALL RFM2gUserMemory(RFM2GHANDLE rh, volatile void **UserMemoryPtr,
    RFM2G_UINT64 Offset, RFM2G_UINT32 Pages);

STDRFM2GCALL RFM2gUserMemoryBytes(RFM2GHANDLE rh, volatile void **UserMemoryPtr,
    RFM2G_UINT64 Offset, RFM2G_UINT32 Bytes);

STDRFM2GCALL RFM2gUnMapUserMemory(RFM2GHANDLE rh, volatile void **UserMemoryPtr,
    RFM2G_UINT32 Pages);

STDRFM2GCALL RFM2gUnMapUserMemoryBytes(RFM2GHANDLE rh, volatile void **UserMemoryPtr,
    RFM2G_UINT32 Bytes);

STDRFM2GCALL RFM2gNodeID(RFM2GHANDLE rh, RFM2G_NODE *NodeIdPtr);

STDRFM2GCALL RFM2gBoardID(RFM2GHANDLE rh, RFM2G_UINT8 *BoardIdPtr);

STDRFM2GCALL RFM2gSize(RFM2GHANDLE rh, RFM2G_UINT32 *SizePtr);

STDRFM2GCALL RFM2gFirst(RFM2GHANDLE rh, RFM2G_UINT32 *FirstPtr);

STDRFM2GCALL RFM2gDeviceName(RFM2GHANDLE rh, char *NamePtr);

STDRFM2GCALL RFM2gDllVersion(RFM2GHANDLE rh, char *VersionPtr);

STDRFM2GCALL RFM2gDriverVersion(RFM2GHANDLE rh, char *VersionPtr);

STDRFM2GCALL RFM2gGetDMAThreshold( RFM2GHANDLE rh, RFM2G_UINT32 *Threshold);

STDRFM2GCALL RFM2gSetDMAThreshold( RFM2GHANDLE rh, RFM2G_UINT32 Threshold);

STDRFM2GCALL RFM2gSetDMAByteSwap(RFM2GHANDLE rh, RFM2G_BOOL byteSwap);

STDRFM2GCALL RFM2gGetDMAByteSwap(RFM2GHANDLE rh, RFM2G_BOOL * byteSwap);

STDRFM2GCALL RFM2gSetPIOByteSwap(RFM2GHANDLE rh, RFM2G_BOOL byteSwap);

STDRFM2GCALL RFM2gGetPIOByteSwap(RFM2GHANDLE  rh, RFM2G_BOOL * byteSwap);

/*****************************************************************************/

/* Data Transfer */

STDRFM2GCALL RFM2gRead(RFM2GHANDLE rh, RFM2G_UINT32 Offset, void *Buffer,
                       RFM2G_UINT32 Length);

STDRFM2GCALL RFM2gWrite(RFM2GHANDLE rh, RFM2G_UINT32 Offset, void *Buffer,
                        RFM2G_UINT32 Length);

STDRFM2GCALL RFM2gPeek8(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                        RFM2G_UINT8  *Value);

STDRFM2GCALL RFM2gPeek16(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                         RFM2G_UINT16 *Value);

STDRFM2GCALL RFM2gPeek32(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                         RFM2G_UINT32 *Value);

/* Implemented only on 64 bit Operating Systems */
STDRFM2GCALL RFM2gPeek64(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
						 RFM2G_UINT64 *Value);

STDRFM2GCALL RFM2gPoke8(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                        RFM2G_UINT8 Value);

STDRFM2GCALL RFM2gPoke16(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                         RFM2G_UINT16 Value);

STDRFM2GCALL RFM2gPoke32(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                         RFM2G_UINT32 Value);

/* Implemented only on 64 bit Operating Systems */
STDRFM2GCALL RFM2gPoke64(RFM2GHANDLE rh, RFM2G_UINT32 Offset,
                         RFM2G_UINT64 Value);

/*****************************************************************************/

/* Interrupt Event Functions */

STDRFM2GCALL RFM2gEnableEvent(RFM2GHANDLE rh, RFM2GEVENTTYPE EventType);

STDRFM2GCALL RFM2gDisableEvent(RFM2GHANDLE rh, RFM2GEVENTTYPE EventType);

STDRFM2GCALL RFM2gSendEvent(RFM2GHANDLE rh, RFM2G_NODE ToNode,
    RFM2GEVENTTYPE EventType, RFM2G_UINT32 ExtendedData);

#define RFM2G_INFINITE_TIMEOUT (unsigned int) 0xFFFFFFFF
#define RFM2G_NO_WAIT (unsigned int) 0x0

STDRFM2GCALL RFM2gWaitForEvent(RFM2GHANDLE rh, RFM2GEVENTINFO *EventInfo);

STDRFM2GCALL RFM2gEnableEventCallback(RFM2GHANDLE rh,
    RFM2GEVENTTYPE EventType,
    RFM2G_EVENT_FUNCPTR pEventFunc);

STDRFM2GCALL RFM2gDisableEventCallback(RFM2GHANDLE rh,
    RFM2GEVENTTYPE EventType);

STDRFM2GCALL RFM2gClearEvent(RFM2GHANDLE rh, RFM2GEVENTTYPE EventType);

STDRFM2GCALL RFM2gCancelWaitForEvent(RFM2GHANDLE rh,
    RFM2GEVENTTYPE EventType);

STDRFM2GCALL RFM2gClearEventCount(RFM2GHANDLE rh, RFM2GEVENTTYPE EventType);

STDRFM2GCALL RFM2gGetEventCount(RFM2GHANDLE rh, RFM2GEVENTTYPE EventType,
	RFM2G_UINT32 *Count);

/*****************************************************************************/

/* Utility */


#if defined(_WINDOWS)
DECL_SPEC(char *)  RFM2gErrorMsg(RFM2G_STATUS ErrorCode);
#else
char * RFM2gErrorMsg(RFM2G_STATUS ErrorCode);
#endif

STDRFM2GCALL RFM2gGetLed(RFM2GHANDLE rh, RFM2G_BOOL *Led);

STDRFM2GCALL RFM2gSetLed(RFM2GHANDLE rh, RFM2G_BOOL Led);

STDRFM2GCALL RFM2gCheckRingCont(RFM2GHANDLE rh);

STDRFM2GCALL RFM2gGetDarkOnDark(RFM2GHANDLE rh, RFM2G_BOOL *state);

STDRFM2GCALL RFM2gSetDarkOnDark(RFM2GHANDLE rh, RFM2G_BOOL state);

STDRFM2GCALL RFM2gClearOwnData(RFM2GHANDLE rh, RFM2G_BOOL *state);

STDRFM2GCALL RFM2gGetTransmit(RFM2GHANDLE rh, RFM2G_BOOL *state);

STDRFM2GCALL RFM2gSetTransmit(RFM2GHANDLE rh, RFM2G_BOOL state);

STDRFM2GCALL RFM2gGetLoopback(RFM2GHANDLE rh, RFM2G_BOOL *state);

STDRFM2GCALL RFM2gSetLoopback(RFM2GHANDLE rh, RFM2G_BOOL state);

STDRFM2GCALL RFM2gGetParityEnable(RFM2GHANDLE rh, RFM2G_BOOL *state);

STDRFM2GCALL RFM2gSetParityEnable(RFM2GHANDLE rh, RFM2G_BOOL state);

STDRFM2GCALL RFM2gGetMemoryOffset(RFM2GHANDLE rh, RFM2G_MEM_OFFSETTYPE *offset);

STDRFM2GCALL RFM2gSetMemoryOffset(RFM2GHANDLE rh, RFM2G_MEM_OFFSETTYPE offset);

STDRFM2GCALL RFM2gGetSlidingWindow(RFM2GHANDLE rh, RFM2G_UINT32 *offset, 
    RFM2G_UINT32 *size);

STDRFM2GCALL RFM2gSetSlidingWindow(RFM2GHANDLE rh, RFM2G_UINT32 offset);

/*****************************************************************************/

/* NOTE: Application programs should not use the following functions unless
         directed to do so by GE Fanuc Intelligent Platforms, Inc. support
         personnel. */

STDRFM2GCALL RFM2gGetDebugFlags(RFM2GHANDLE rh, RFM2G_UINT32 *Flags);

STDRFM2GCALL RFM2gSetDebugFlags(RFM2GHANDLE rh, RFM2G_UINT32 Flags);

STDRFM2GCALL RFM2gWriteReg(RFM2GHANDLE rh, RFM2GREGSETTYPE regset,
    RFM2G_UINT32 Offset, RFM2G_UINT32 Width, RFM2G_UINT32 Value);

STDRFM2GCALL RFM2gReadReg(RFM2GHANDLE rh, RFM2GREGSETTYPE regset,
    RFM2G_UINT32 Offset, RFM2G_UINT32 Width, void *Value);

STDRFM2GCALL RFM2gSetReg(RFM2GHANDLE rh, RFM2GREGSETTYPE regset,
    RFM2G_UINT32 Offset, RFM2G_UINT32 Width, RFM2G_UINT32 Mask);

STDRFM2GCALL RFM2gClearReg(RFM2GHANDLE rh, RFM2GREGSETTYPE regset,
    RFM2G_UINT32 Offset, RFM2G_UINT32 Width, RFM2G_UINT32 Mask);

STDRFM2GCALL RFM2gMapDeviceMemory(RFM2GHANDLE rh, RFM2GREGSETTYPE regset, 
    volatile void **DeviceMemoryPtr);

STDRFM2GCALL RFM2gUnMapDeviceMemory(RFM2GHANDLE rh, RFM2GREGSETTYPE regset, 
    volatile void **DeviceMemoryPtr);


#ifdef __cplusplus
}
#endif

#endif  /* __RFM2G_API_H */
