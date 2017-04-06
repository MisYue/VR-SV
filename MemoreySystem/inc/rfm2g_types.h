/*
===============================================================================
                            COPYRIGHT NOTICE

    Copyright (C) 2001,2006, 2008 GE Fanuc Embedded Systems, Inc.
    International Copyright Secured.  All Rights Reserved.

-------------------------------------------------------------------------------
    Description: Type Specifications for the RFM2G Library
-------------------------------------------------------------------------------

    $Workfile: rfm2g_types.h $
    $Revision: 5 $
    $Modtime: 8/04/08 5:55p $

===============================================================================
*/

#ifndef __RFM2G_TYPES_H
#define __RFM2G_TYPES_H


/*****************************************************************************/

/* Provide Type Definitions for basic portable types*/
typedef unsigned char           RFM2G_UINT8;
typedef unsigned short		    RFM2G_UINT16;
typedef unsigned long           RFM2G_UINT32;
typedef unsigned __int64		RFM2G_UINT64; 

typedef signed char             RFM2G_INT8;
typedef signed short	        RFM2G_INT16;
typedef signed long             RFM2G_INT32;
typedef __int64				    RFM2G_INT64;
typedef signed char             RFM2G_CHAR;

typedef unsigned char           RFM2G_BOOL;
#ifndef ULONG_PTR
	typedef ULONG				RFM2G_ADDR;
#else
	typedef ULONG_PTR			RFM2G_ADDR;
#endif

/* We also use void * and char *, but these are 
   C standard types, and do not need to be declares */


/*****************************************************************************/

/* Add base constants for the Boolean */
#define RFM2G_TRUE  ((RFM2G_BOOL) 1)
#define RFM2G_FALSE ((RFM2G_BOOL) 0)

/*****************************************************************************/

/* Define the scalar types */

typedef RFM2G_UINT16      RFM2G_NODE;    /* Node ID values               */
typedef RFM2G_INT32       RFM2GRESULT;  /* Return codes for functions   */


/*****************************************************************************/

/* Define symbols to specify data width */
typedef enum rfm2gDataWidth
{
  RFM2G_BYTE      = 1,
  RFM2G_WORD      = 2,
  RFM2G_LONG      = 4,
  RFM2G_LONGLONG  = 8
} RFM2GDATAWIDTH;


/*****************************************************************************/


/*****************************************************************************/

#endif  /* __RFM2G_TYPES_H */
