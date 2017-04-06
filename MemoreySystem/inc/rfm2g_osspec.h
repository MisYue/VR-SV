/*
 *--------------------------------------------------------------------------
 *                       COPYRIGHT NOTICE
 *
 *  Copyright (C) 1997-2006 GE Fanuc Embedded Systems, Inc.
 *  International Copyright Secured.  All Rights Reserved.
 *
 *--------------------------------------------------------------------------
 *
 *  $Workfile: rfm2g_osspec.h $
 *  $Revision: 9 $
 *  $Modtime: 8/21/08 3:45p $
 *
 *--------------------------------------------------------------------------
 * DESCRIPTION  This file 
 * 1) define STDRFM2GCALL which is used for functions that return RFM2G_STATUS 
 * 2) define RFM2GHANDLE
 * 3) prototypes for driver specific functions
 * 4) include other header files as necessary.
 * 5) include common API definitions header file rfm2g_defs.h
 * 6) Include header file that defines RFM2G types, rfm2g_types.h 
 *--------------------------------------------------------------------------
 */
#ifndef	_RFM2G_OSSPEC_H_
#define	_RFM2G_OSSPEC_H_

#include "rfm2g_defs.h"
#include "rfm2g_regs.h"
#include "pmc5565_nt.h"

/*****************************************************************************
*	Macro used to declare functions
*****************************************************************************/
#if	(_MSC_VER == 1200)

	#if defined(DEFINE_CODE)
		#define	DECL_SPEC(Type)	__declspec(dllexport)	Type	__cdecl
	#else
		#define	DECL_SPEC(Type)	__declspec(dllimport)	Type	__cdecl
	#endif

#elif (_MSC_VER == 1400)

	#if defined(DEFINE_CODE)
		#define	DECL_SPEC(Type)	__declspec(dllexport)	Type	__cdecl
	#else
		#define	DECL_SPEC(Type)	Type	__cdecl
	#endif

#else

	#if defined(DEFINE_CODE)
		#define	DECL_SPEC(Type)	Type	__cdecl
	#else
		#define	DECL_SPEC(Type)	Type	__cdecl
	#endif

#endif

/*****************************************************************************
*	Macro used to declare functions in common API
*****************************************************************************/
#define STDRFM2GCALL	DECL_SPEC(RFM2G_STATUS)

/*****************************************************************************
*	Structure used to maintain a list of objects.
*****************************************************************************/
typedef	struct	_OVLINFO
{
			OVERLAPPED	Ovl;
			LONG		ElemId;
	struct	_OVLINFO	*pNext;
	struct	_OVLINFO	*pPrev;
			DWORD		ThrdId;
}
OVLINFO;

/*************************************************************************
*	Structure needed to maintain info about each of the interrupts.
*************************************************************************/
typedef	struct
{
	OVLINFO		*pOvl;
	HANDLE		hCnclEvnt;
	DWORD		*pThrdId;
}
INTINFO;

/*************************************************************************
*	Structure needed to maintain info about each of the callbacks.
*************************************************************************/
typedef	struct
{
	void			(*pCbFunc)(void *, RFM2GEVENTINFO *);
	void			*pHandle;
	int				Status;
	HANDLE			hThread;
	HANDLE			hStrtEvnt;
	RFM2GEVENTTYPE	Type;
}
CALLBACKINFO;

/*****************************************************************************
*	This info is used to maintain a list of info needed to connect
*	to an instance of an RFM board in a given process.
*****************************************************************************/
typedef	struct	_DEVINST
{
	/*******************************************************************
	*	Info needed to maintain the list of DEVINST structures
	*******************************************************************/
	struct _DEVINST	*pNext;
	LONG			RefCnt;
	LONG			DevInst;

	/*******************************************************************
	*	Handle to driver for this instance
	*******************************************************************/
	HANDLE			hDriver,hOVLDriver;

	/*******************************************************************
	*	Info for memory, RFM registers and PLX registers
	*******************************************************************/
	rfmMapMemory_t	RfmMem; 
	rfmMapMemory_t	RfmRegs; 
	rfmMapMemory_t	PlxRegs; 

	/*******************************************************************
	*	Event info needed to manage interrupts / overlapped IO
	*******************************************************************/
	INTINFO			IntInfo[RFM2GEVENT_LAST];
	OVLINFO			*pOvlRd;
	OVLINFO			*pOvlWr;

	/*******************************************************************
	*	User call back info
	*******************************************************************/
	HANDLE			hCbMutex;
	CALLBACKINFO	CbInfo[RFM2GEVENT_LAST];

	/*******************************************************************
	*	Config info for this board instance
	*******************************************************************/
	RFM2GCONFIG		CfgInfo;
	LONG			RfmRegSz;

	/*******************************************************************
	*	Swap info is shared among all processes that open this instance
	*******************************************************************/
	HANDLE			hSwMutex;
	RFM2G_BOOL		*pDMASwap;
	RFM2G_BOOL		*pPIOSwap;

	/****************************************************************
	*	Debug flags
	****************************************************************/
	RFM2G_UINT32	DbgFlags;

	/****************************************************************
	*	Internal info managed by DLL code
	****************************************************************/
	void			*pInternal;
}
DEVINST;

typedef	struct
{
	/****************************************************************
	*	Info specific to a specified device for current process
	****************************************************************/
	DEVINST			*pDevInst;

	/****************************************************************
	*	Special ID to verify this structure
	****************************************************************/
	RFM2G_UINT32	struct_id;

	/****************************************************************
	*	ThreadId that opened this instance 
	****************************************************************/
	DWORD			ThreadId;
}
_RFM2GHANDLE, *RFM2GHANDLE;

/*************************************************************************
*	Macros used to access the RFM registers
*************************************************************************/
#define	DECL_RFMBASE(h)	volatile RFM pRBase = (RFM)(h->pDevInst->RfmRegs.rmm_rfm)
#define	RFM_ACC(reg)	(pRBase->reg)
#define	RFM_FLUSH()		{ UCHAR Dummy = (UCHAR)(pRBase->rfm3_bid); }

/*************************************************************************
*	Macros used to access the PLX registers
*************************************************************************/
typedef	RFMOR	PLX;
#define	DECL_PLXBASE(h)	volatile PLX pPBase = (PLX)(h->pDevInst->PlxRegs.rmm_rfm)
#define	PLX_ACC(reg)	(pPBase->reg)
#define	PLX_FLUSH()		{ ULONG Dummy = (UCHAR)(pPBase->rfm3rr_cmd); }

#endif
