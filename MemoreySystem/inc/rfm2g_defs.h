/*
===============================================================================
                            COPYRIGHT NOTICE

Copyright (c) 2001, 2006-2008, GE Fanuc Intelligent Platforms, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.  Redistributions in binary
form must reproduce the above copyright notice, this list of conditions and
the following disclaimer in the documentation and/or other materials provided
with the distribution.  Neither the name of the GE Fanuc Intelligent Platforms, Inc.
nor the names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

-------------------------------------------------------------------------------

$Workfile: rfm2g_defs.h $
$Revision: 32 $
$Modtime: 2/20/08 12:11p $

-------------------------------------------------------------------------------
    Description: RFM2G Common API Library Definitions
-------------------------------------------------------------------------------


==============================================================================*/

#ifndef __RFM2G_DEFS_H
#define __RFM2G_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/

/* Standard defines */
#include "rfm2g_types.h"
#include "rfm2g_errno.h"

/*
 * This header file should
 *
 * 1) Define definitions for use with RFM2G_BOOL
 * 2) Define definitions for use with RFM2G_NODE
 * 3) Define RFM2GCONFIG
 * 4) Define RFM2GEVENTTYPE enumeration type
 * 5) Define RFM2GEVENTINFO structure type
 * 6) Define driver debug message class definitions
 */

/*****************************************************************************/

/* Definitions for use with RFM2G_BOOL */

#define RFM2G_ENABLE  RFM2G_TRUE
#define RFM2G_DISABLE RFM2G_FALSE

#define RFM2G_ON      RFM2G_TRUE
#define RFM2G_OFF     RFM2G_FALSE

/*****************************************************************************/

/* Definitions for use with RFM2G_NODE */

#define  RFM2G_NODE_MIN          0      /* Smallest legal node               */
#define  RFM2G_NODE_MAX          255    /* Largest legal node                */

#define  RFM2G_NODE_SPECIAL_MIN  0xFFFE
#define  RFM2G_NODE_UNKNOWN      0xFFFE /* Unknown Node                      */
#define  RFM2G_NODE_ALL          0xFFFF /* All Nodes                         */
#define  RFM2G_NODE_SPECIAL_MAX  0xFFFF

/*****************************************************************************/

/* RFM2GCONFIG structure is used by the RFM2gGetConfig function.  */

typedef struct rfm2gPciConfig
{
    RFM2G_UINT8     bus;            /* PCI bus number                        */
    RFM2G_UINT8     function;       /* Function                              */
    RFM2G_UINT16    type;           /* From Device ID register               */
    RFM2G_UINT32    devfn;          /* Encoded device and function numbers   */
    RFM2G_UINT8     revision;       /* Revision of RFM board                 */

    /* RFM PCI Memory Acc. Local, Runtime, and DMA Register Info */
    /* Base Address Register 0 */
    RFM2G_UINT32    rfm2gOrBase;      /* Physical base addr of board registers */
    RFM2G_UINT32    rfm2gOrWindowSize;/* Size of PCI Memory window             */
    RFM2G_UINT32    rfm2gOrRegSize;   /* Actual Memory space size              */


    /* RFM Memory Acc. Control and Status Register Info */
    /* Base Address Register 2 */
    RFM2G_UINT32    rfm2gCsBase;      /* Physical base addr of board registers*/
    RFM2G_ADDR    rfm2gCsWindowSize;/* Size of PCI Memory window            */
    RFM2G_UINT32    rfm2gCsRegSize;   /* Actual Memory space size             */

    /* RFM board memory space info */
    /* Base Address Register 3 */
    RFM2G_UINT32    rfm2gWindowSize;/* Size of PCI Memory Window             */

    RFM2G_ADDR    rfm2gBase;      /* Physical base address of board memory */
    /* Interrupt Info */
    RFM2G_UINT8     interruptNumber;  /* Which interrupt ? */

} RFM2GPCICONFIG;

/*****************************************************************************/

/* RFM2GCONFIG structure is used by the RFM2gGetConfig function.  */

typedef struct RFM2GCONFIG_
{
    RFM2G_NODE     NodeId;             /* Node ID of board                   */
    RFM2G_UINT8    BoardId;            /* Board Type ID                      */
    RFM2G_UINT8    Unit;               /* Device unit number                 */
    RFM2G_UINT8    PlxRevision;        /* Revision of PLX chip               */
    RFM2G_UINT32   MemorySize;         /* Total Board Memory                 */
    char           Device[128];        /* Name of device file                */
    char           Name[32];/* Product ordering option "VMISFT-RFM2G-ABC-DEF"*/
    char           DriverVersion[16];  /* Release level of driver            */
    RFM2G_UINT8    BoardRevision;      /* Revision of RFM board              */
    RFM2G_UINT8    RevisionId;         /* PCI Revision ID                    */
    RFM2G_UINT32   Lcsr1;              /* Local Control Status Reg - copy    */
    RFM2GPCICONFIG PciConfig;          /* PCI Bus Specific Info              */
    RFM2G_UINT16   BuildId;     /* Build Id of the Revision of the RFM board */
} RFM2GCONFIG;

/*****************************************************************************/

/* Interrupt Events */

typedef enum rfm2gEventType
{
   RFM2GEVENT_RESET,       /* Reset Interrupt                                */
   RFM2GEVENT_INTR1,       /* Network Interrupt 1                            */
   RFM2GEVENT_INTR2,       /* Network Interrupt 2                            */
   RFM2GEVENT_INTR3,       /* Network Interrupt 3                            */
   RFM2GEVENT_INTR4,       /* Network Interrupt 4 (Init interrupt)           */
   RFM2GEVENT_BAD_DATA,    /* Bad Data                                       */
   RFM2GEVENT_RXFIFO_FULL, /* RX FIFO has been full one or more times.       */
   RFM2GEVENT_ROGUE_PKT,   /* the board detected and removed a rogue packet. */
   RFM2GEVENT_RXFIFO_AFULL,/* RX FIFO has been almost full one or more times.*/
   RFM2GEVENT_SYNC_LOSS,   /* Sync loss has occured one of more times.       */
   RFM2GEVENT_MEM_WRITE_INHIBITED, /* Write to local memory was attempted and inhibited */
   RFM2GEVENT_LOCAL_MEM_PARITY_ERR, /* Parity errors have been detected on local memory accesses */
   RFM2GEVENT_LAST         /* Number of Events                               */
}  RFM2GEVENTTYPE;

/*****************************************************************************/

/* Information about received or transmitted interrupt events */

typedef struct rfm2gEventInfo
{
    RFM2G_UINT32   ExtendedInfo; /* Data passed with event                  */
    RFM2GEVENTTYPE Event;        /* Event type union                        */
    RFM2G_UINT32   Timeout;      /* timeout value to wait for event mSec    */
    RFM2G_NODE     NodeId;       /* Source Node                             */
    void *         pDrvSpec;     /* Driver specific                         */
} RFM2GEVENTINFO;

/*****************************************************************************/

/* Driver debug message class definitions */

#define RFM2G_DBERROR         (1<<0)   /* Report critical errors             */
#define RFM2G_DBINIT          (1<<1)   /* Trace device probing and search    */
#define RFM2G_DBINTR          (1<<2)   /* Trace interrupt service            */
#define RFM2G_DBIOCTL         (1<<3)   /* Trace ioctl(2) system calls        */
#define RFM2G_DBMMAP          (1<<4)   /* Trace mmap(2) system calls         */
#define RFM2G_DBOPEN          (1<<5)   /* Trace open(2) system calls         */
#define RFM2G_DBCLOSE         (1<<6)   /* Trace close(2) system calls        */
#define RFM2G_DBREAD          (1<<7)   /* Trace read(2) system calls         */
#define RFM2G_DBWRITE         (1<<8)   /* Trace write(2) system calls        */
#define RFM2G_DBPEEK          (1<<9)   /* Trace peeks                        */
#define RFM2G_DBPOKE          (1<<10)  /* Trace pokes                        */
#define RFM2G_DBSTRAT         (1<<11)  /* Trace read/write strategy          */
#define RFM2G_DBTIMER         (1<<12)  /* Trace interval timer               */
#define RFM2G_DBTRACE         (1<<13)  /* Trace subroutine entry/exit        */
#define RFM2G_DBMUTEX         (1<<14)  /* Trace synchronization and locking  */
#define RFM2G_DBINTR_NOT      (1<<15)  /* Trace non-RFM interrupt service    */
#define RFM2G_DBSLOW          (1<<16)  /* Let syslogd get the message        */
#define RFM2G_DBMINPHYS       (1<<17)  /* Trace minphys limits               */
#define RFM2G_DBDMA			  (1<<18)  /* Trace DMA Calls					 */

/*****************************************************************************/

/* RFM2GREGSETTYPE is used by RFM2gRegWrite and RFM2gRegRead functions  */

typedef enum rfm2gRegSetType
{
   RFM2GCFGREGMEM,   /* BAR 0 mem - Local Config, Runtime and DMA Registers  */
   RFM2GCFGREGIO,    /* BAR 1 I/O - Local Config, Runtime and DMA Registers  */
   RFM2GCTRLREGMEM,  /* BAR 2 mem - RFM Control and Status Registers         */
   RFM2GMEM,         /* BAR 3 mem - reflective memory RAM                    */
   RFM2GRESERVED0REG,/* BAR 4 Reserved                                       */
   RFM2GRESERVED1REG /* BAR 5 Reserved                                       */
}  RFM2GREGSETTYPE;

/*****************************************************************************/

/* RFM2G_MEM_WINDOWTYPE is used by RFM2gSetMemoryWindow and RFM2gGetMemoryWindow functions  */

typedef enum rfm2gMemWindowType
{
   RFM2G_MEM_OFFSET0,  /* 1st 64 MB Memory offset                            */
   RFM2G_MEM_OFFSET1,  /* 2nd 64 MB Memory offset                            */
   RFM2G_MEM_OFFSET2,  /* 3rd 64 MB Memory offset                            */
   RFM2G_MEM_OFFSET3,  /* 4th 64 MB Memory offset                            */
}  RFM2G_MEM_OFFSETTYPE;

#ifdef __cplusplus
}
#endif

#endif
