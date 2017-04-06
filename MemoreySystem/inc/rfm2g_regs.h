/*
===============================================================================
                            COPYRIGHT NOTICE

Copyright (c) 2006, 2008, GE Fanuc Intelligent Platforms, Inc.
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
$Workfile: rfm2g_regs.h $
$Revision: 17 $
$Modtime: 6/24/08 4:21p $
-------------------------------------------------------------------------------
    Description: Reflective Memory hardware register offset definitions
-------------------------------------------------------------------------------

    Revision History:
    Date         Who  Ver   Reason For Change
    -----------  ---  ----  ---------------------------------------------------
    11-OCT-2001  ML   1.0   Created.

===============================================================================
*/


#ifndef __RFM2G_REGS_H
#define __RFM2G_REGS_H


/* Device IDs of supported PCI, PMC, and CPCI Reflective Memory boards       */
#define  DEVICE_ID_PCI5565    0x5565    /* VMIPCI-5565 Device ID             */

/* Offsets of Runtime Registers                                              */
#define  rfmor_intcsr      0x68         /* Interrupt control and status      */
#define  rfmor_cntrl       0x6c         /* Control                           */
#define  rfmor_revision    0x74         /* RFM2g Revision                    */
#define  rfmor_DmaMode0    0x80         /* DMA Channel 0 Mode                */
#define  rfmor_DmaPciAddr0 0x84         /* DMA Channel 0 PCI Address         */
#define  rfmor_DmaLocAddr0 0x88         /* DMA Channel 0 Local Address       */
#define  rfmor_DmaCount0   0x8c         /* DMA Channel 0 Transfer Byte Count */
#define  rfmor_DmaPtr0     0x90         /* DMA Channel 0 Descriptor Pointer  */
#define  rfmor_Dma0Csr     0xa8         /* DMA Command / Status Register     */
#define  rfmor_Dma1Csr     0xa9         /* DMA Command / Status Register     */
#define  rfmor_DmaArb      0xac         /* Mode / DMA Arbitration            */
#define  rfmor_DmaThresh   0xb0         /* DMA Threshold                     */
#define  rfmor_DmaDac0     0xb4         /* DMA Channel 0 PCI Dual Access Cyc */
#define  rfmor_lbrd0       0x18         /* Local Address Space 0             */
#define  rfmor_endian_desc 0x0C         /* Endian                            */
#define  rfmor_las1rr      0xf0         /* Local Addr Space 1 Range Register */
#define  rfmor_las1ba      0xf4         /* Local Addr Space 1 Base Address   */

#define RFM2G_IOREGSIZE    0x40

/* Definition of the rfmor_intcsr (interrupt control/status) register        */
#define  RFMOR_INTCSR_LSERR         (1<<0)  /* Enable TEA/LSERR              */
#define  RFMOR_INTCSR_ENABLEPTY     (1<<6)  /* Enable Data Parity Check      */
#define  RFMOR_INTCSR_PTYSTATUS     (1<<7)  /* Parity Error Status           */
#define  RFMOR_INTCSR_ENABLEINT     (1<<8)  /* Enable PCI Interrut           */
#define  RFMOR_INTCSR_ENABLELOCINT  (1<<11) /* Enable Local interrupt        */
#define  RFMOR_INTCSR_LOCINT        (1<<15) /* Enable Local interrupt        */
#define  RFMOR_INTCSR_ENABLEDMA0INT (1<<18) /* Enable DMA0 interupt          */
#define  RFMOR_INTCSR_ENABLEDMA1INT (1<<19) /* Enable DMA1 interrupt         */
#define  RFMOR_INTCSR_DMA0INT       (1<<21) /* DMA0 interrupt active         */
#define  RFMOR_INTCSR_DMA1INT       (1<<22) /* DMA1 interrupt active         */

/* Definition of the rfmor_DmaMode0 register                                 */
#define  RFMOR_DMAMODE_32BIT_BUS    (3<<0)
#define  RFMOR_DMAMODE_TA_READY     (1<<6)
#define  RFMOR_DMAMODE_BTERM        (1<<7)
#define  RFMOR_DMAMODE_LOCAL_BURST  (1<<8)
#define  RFMOR_DMAMODE_DONE_INT     (1<<10)
#define  RFMOR_DMAMODE_INT_TO_PCI   (1<<17)

/* Definitions of the rfmor_DmaPtr0 register */
#define  RFMOR_DMAPTR_TO_PCI        (1<<3)

/* Definitions of the rfmor_DmaCsr register */
#define  RFMOR_DMACSR_ENABLE        (1<<0)
#define  RFMOR_DMACSR_START         (1<<1)
#define  RFMOR_DMACSR_CLEAR_INT     (1<<3)

/* Definitions of the rfmor_las1rr register */
#define  RFMOR_LAS1RR_RANGE_MASK    0xFFFFFFF0
#define  RFMOR_LAS1RR_RANGE_2M      0xFFE00000
#define  RFMOR_LAS1RR_RANGE_16M     0xFF000000
#define  RFMOR_LAS1RR_RANGE_64M     0xFC000000
#define  RFMOR_LAS1RR_RANGE_128M    0xF8000000
#define  RFMOR_LAS1RR_RANGE_256M    0xF0000000

/* Definitions of the rfmor_las1ba register */
#define  RFMOR_LAS1BA_ENABLE_LAS1   (1<<0)  /* Enable Local Address Space 1 */


/* Offsets of memory space registers that are common to all supported boards */
#define  rfm2g_brv         0x00      /* Board Revision / Model               */
#define  rfm2g_bid         0x01      /* Board ID register (ro)               */
#define  rfm2g_build_id    0x02      /* Build ID register (ro)               */
#define  rfm2g_nid         0x04      /* Node ID register (ro)                */
#define  rfm2g_lcsr        0x08      /* Local control and status register    */
#define  rfm2g_lisr        0x10      /* Local interrupt status register      */
#define  rfm2g_lier        0x14      /* Local interrupt enable register      */
#define  rfm2g_ntd         0x18      /* Network Target Data                  */
#define  rfm2g_ntn         0x1c      /* Network Target Node                  */
#define  rfm2g_nic         0x1d      /* Network Interrupt Command            */
#define  rfm2g_isd1        0x20      /* INT1 Sender Data                     */
#define  rfm2g_sid1        0x24      /* INT1 Sender ID                       */
#define  rfm2g_isd2        0x28      /* INT2 Sender Data                     */
#define  rfm2g_sid2        0x2c      /* INT2 Sender ID                       */
#define  rfm2g_isd3        0x30      /* INT3 Sender Data                     */
#define  rfm2g_sid3        0x34      /* INT3 Sender ID                       */
#define  rfm2g_initd       0x38      /* Initialized Node Data                */
#define  rfm2g_initn       0x3c      /* Initialized Node ID                  */

#define  RFM2G_REGSIZE     0x40      /* Space reserved for registers         */

/* Definition of the rfm2g_bid (board ID) register for supported boards      */
#define  RFM2G_BID_5565    0x65      /* VMIPMC-5565                          */

/* Defnintion of the rfm2g_lcsr (Local control and status) register          */
#define  RFM2G_LCSR_LED     (1<<31)  /* 0 => LED is off 1=> LED is on        */
#define  RFM2G_LCSR_XMTDIS  (1<<30)  /* 1 => Disable transmitter             */
#define  RFM2G_LCSR_DOD     (1<<29)  /* Dark on Dark enable                  */
#define  RFM2G_LCSR_LOOP    (1<<28)  /* Loopback enable                      */
#define  RFM2G_LCSR_PTY     (1<<27)  /* Local Bus Parity enable              */
#define  RFM2G_LCSR_CFG     (3<<20)  /* Configured Memory Size               */
#define  RFM2G_LCSR_OFF0    (1<<16)  /* Offset 0 control bit                 */
#define  RFM2G_LCSR_OFF1    (1<<17)  /* Offset 1 control bit                 */
#define  RFM2G_LCSR_RCVFULL (1<<5)   /* Receive fifo full                    */
#define  RFM2G_LCSR_SNCLOST (1<<3)   /* Sync Loss                            */
#define  RFM2G_LCSR_SIGDET  (1<<2)   /* Receive Signal detected              */
#define  RFM2G_LCSR_BADDATA (1<<1)   /* Bad data detected                    */
#define  RFM2G_LCSR_OWNDATA (1<<0)   /* Received data from own node          */

/* Definition fo the rfm2g_lisr (Local interrupt Control) register           */
#define  RFM2G_LISR_AUTOCLR (1<<15)  /* Auto Clear flag                      */
#define  RFM2G_LISR_GBLINT  (1<<14)  /* Global Interrupt Enable              */
#define  RFM2G_LISR_PTYERR  (1<<13)  /* Local Memory Parity Error            */
#define  RFM2G_LISR_WRINIB  (1<<12)  /* 16,8 bit Mem Write Inhibited         */
#define  RFM2G_LISR_SNCLOST (1<<11)  /* Latched Sync Lost                    */
#define  RFM2G_LISR_RXFULL  (1<<10)  /* Receive Fifo Full, Latched           */
#define  RFM2G_LISR_RXAFULL (1<<9)   /* Receive Fifo Almost Full, Latched    */
#define  RFM2G_LISR_BADDATA (1<<8)   /* Invalid data received, latched       */
#define  RFM2G_LISR_INITINT (1<<7)   /* Pending Init Interrupt Received      */
#define  RFM2G_LISR_ROGUE_PKT (1<<6) /* Rogue Packet Fault*/
#define  RFM2G_LISR_RSTREQ  (1<<3)   /* Pending Reset Node Request           */
#define  RFM2G_LISR_INT3    (1<<2)   /* Type2 Int Received                   */
#define  RFM2G_LISR_INT2    (1<<1)   /* Type1 Int Received                   */
#define  RFM2G_LISR_INT1    (1<<0)   /* Type0 Int Received                   */
#define  RFM2G_LISR_UNUSED  0x00004000
#define  RFM2G_LISR_DISABLE 0xFFFF03F3

/* Definition of the rfm2g_lier (Local interrupt enable) register            */
#define RFM2G_LIER_AUTO_CLR (1<<15)  /* Auto Clear Interrupt Enable          */
#define RFM2G_LIER_PTYERR   (1<<13)  /* Parity Error Interrupt Enable        */
#define RFM2G_LIER_WRINIB   (1<<12)  /* Memory Write Inhibit Interrupt Enable*/
#define RFM2G_LIER_SNCLOST  (1<<11)  /* Sync Loss Interrupt Enable           */
#define RFM2G_LIER_RXFULL   (1<<10)  /* Receive Fifo Full Interrupt Enable   */
#define RFM2G_LIER_RXAFULL  (1<<9)   /* Receive Fifo ALmost Full Int Enable  */
#define RFM2G_LIER_BAD_DATA (1<<8)   /* Bad Data Interrupt Enable            */
#define RFM2G_LIER_INITINT  (1<<7)   /* Pending Init Interrupt Enable        */
#define RFM2G_LIER_ROGUE_PKT (1<<6)  /* Rogue packet detect Interrupt Enable */
#define RFM2G_LIER_RSTREQ   (1<<3)   /* Reset Node Request Interrupt Enable  */
#define RFM2G_LIER_INT3     (1<<2)   /* Net Int 3 Enable                     */
#define RFM2G_LIER_INT2     (1<<1)   /* Net Int 2 Enable                     */
#define RFM2G_LIER_INT1     (1<<0)   /* Net Int 1 Enable                     */

/* Definition of the rfm2g_nic (Network Interrupt Command) register         */
#define RFM2G_NIC_RSTREQ    (0x00)   /* Reset Node Request Command          */
#define RFM2G_NIC_INT1      (0x01)   /* Net Int 1                           */
#define RFM2G_NIC_INT2      (0x02)   /* Net Int 2                           */
#define RFM2G_NIC_INT3      (0x03)   /* Net Int 3                           */
#define RFM2G_NIC_RSVD      (0x04)   /* Reserved, used for OWN test         */
#define RFM2G_NIC_INITINT   (0x07)   /* Net Initialized Int                 */
#define RFM2G_NIC_GLOBAL    (0x08)   /* Global Command bit                  */

/* Shape of the RFM2GOR_CNTRL (Serial EEPROM control / init) register */
#define RFM2GOR_CNTRL_READCMD_MASK (0x0F<<0)  /* PCI Read Command Code  */
#define RFM2GOR_CNTRL_MRMUL_CMD	   (0x0C<<0)  /* Memory Read Multiple   */

#endif /* __RFM2G_REGS_H */
