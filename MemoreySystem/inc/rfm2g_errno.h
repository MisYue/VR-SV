/*
===============================================================================
                            COPYRIGHT NOTICE

    Copyright (C) 2003, 2006, 2008, GE Fanuc Intelligent Platforms, Inc.
    International Copyright Secured.  All Rights Reserved.

-------------------------------------------------------------------------------

    $Workfile: rfm2g_errno.h $
    $Revision: 13 $
    $Modtime: 2/20/08 12:11p $

-------------------------------------------------------------------------------
    Description: RFM2G API Library Error Codes
-------------------------------------------------------------------------------

==============================================================================*/

#ifndef	RFM2G_ERRNO_H
#define RFM2G_ERRNO_H

#ifdef	__cplusplus
extern "C"	{
#endif	/* __cplusplus */

/*
 *========================================================================
 * RFM2G Library Error Codes
 *------------------------------------------------------------------------
 *========================================================================
 */
typedef enum RFM2G_STATUS_enum
    {
    RFM2G_SUCCESS,              /* No error                      */
    RFM2G_NOT_IMPLEMENTED,      /* Capability not implemented    */
    RFM2G_DRIVER_ERROR,         /* Nonspecific error             */
    RFM2G_TIMED_OUT,            /* A wait timed out              */
    RFM2G_LOW_MEMORY,           /* A memory allocation failed    */
    RFM2G_MEM_NOT_MAPPED,       /* Memory is not mapped          */
    RFM2G_OS_ERROR,             /* OS defined error              */
    RFM2G_EVENT_IN_USE,         /* Event is being waited on      */
    RFM2G_NOT_SUPPORTED,        /* Capability not supported      */
    RFM2G_NOT_OPEN,             /* Device not open               */
    RFM2G_NO_RFM2G_BOARD,       /* Device not open               */
    RFM2G_BAD_PARAMETER_1,      /* Function Parameter 1 invalid  */
    RFM2G_BAD_PARAMETER_2,      /* Function Parameter 2 invalid  */
    RFM2G_BAD_PARAMETER_3,      /* Function Parameter 3 invalid  */
    RFM2G_BAD_PARAMETER_4,      /* Function Parameter 4 invalid  */
    RFM2G_BAD_PARAMETER_5,      /* Function Parameter 5 invalid  */
    RFM2G_BAD_PARAMETER_6,      /* Function Parameter 6 invalid  */
    RFM2G_BAD_PARAMETER_7,      /* Function Parameter 7 invalid  */
    RFM2G_BAD_PARAMETER_8,      /* Function Parameter 8 invalid  */
    RFM2G_BAD_PARAMETER_9,      /* Function Parameter 9 invalid  */
    RFM2G_OUT_OF_RANGE,         /* Board offset/range exceeded   */
    RFM2G_MAP_NOT_ALLOWED,      /* Board Offset is not legal     */
    RFM2G_LINK_TEST_FAIL,       /* Link Test failed              */
    RFM2G_MEM_READ_ONLY,        /* Outside of User Memory Area   */
    RFM2G_UNALIGNED_OFFSET,     /* Offset not aligned for width  */
    RFM2G_UNALIGNED_ADDRESS,    /* Address not aligned for width */
    RFM2G_LSEEK_ERROR,          /* lseek operation failed        */
    RFM2G_READ_ERROR,           /* read operation failed         */
    RFM2G_WRITE_ERROR,          /* write operation failed        */
    RFM2G_HANDLE_NOT_NULL,      /* Non-NULL handle init request  */
    RFM2G_MODULE_NOT_LOADED,    /* Driver not loaded             */
    RFM2G_NOT_ENABLED,          /* Interrupt not enabled         */
    RFM2G_ALREADY_ENABLED,      /* Interrupt already enabled     */
    RFM2G_EVENT_NOT_IN_USE,     /* No process waiting on int     */
    RFM2G_BAD_RFM2G_BOARD_ID,   /* Invalid RFM2G Board ID        */
    RFM2G_NULL_DESCRIPTOR,      /* RFM2G Handle is null          */
    RFM2G_WAIT_EVENT_CANCELED,  /* Event Wait Canceled           */
    RFM2G_DMA_FAILED,           /* DMA failed                    */
    RFM2G_NOT_INITIALIZED,      /* User has not called RFM2gInit() yet */
    RFM2G_UNALIGNED_LENGTH,     /* Data transfer length not 4 byte aligned */
	RFM2G_SIGNALED,             /* Signal from OS                */
	RFM2G_NODE_ID_SELF,         /* Cannot send event to self     */
    RFM2G_MAX_ERROR_CODE
    } RFM2G_STATUS;

/* Lookup table */

extern const int	rfm2g_nerr;
extern const char	*rfm2g_errlist[];

#ifdef	__cplusplus
};
#endif	/* __cplusplus */

#endif	/* RFM2G_ERRNO_H */
