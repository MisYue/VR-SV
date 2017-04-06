/*
 *--------------------------------------------------------------------------
 *                       COPYRIGHT NOTICE
 *
 *  Copyright (C) 2000-2006 GE Fanuc Embedded Systems, Inc.
 *  International Copyright Secured.  All Rights Reserved.
 *--------------------------------------------------------------------------
 *
 *  $Workfile: pmc5565_nt.h $
 *  $Revision: 4 $
 *  $Modtime: 8/08/08 5:56p $
 *
 *--------------------------------------------------------------------------
 *	
 *--------------------------------------------------------------------------
 */

 #ifndef	_PMC5565_NT_H_
#define	_PMC5565_NT_H_

#include "rfm2g_defs.h"

/*
 *------------------------------------------------------------------------
 * Before you begin: there are several sets of registers associated with
 * a PCI hardware device.  Below is an explanation of how these are used
 * with VMIC's RFM products.
 *------------------------------------------------------------------------
 * The VMIPMC-5565 reflective memory devices have three sets of registers:
 *
 * I) PCI Configuration Space Registers; these registers are used by the
 * host CPU firmware to dynamically configure the PCI busses while the
 * system boots. Using the information in these registers, the CPU
 * firmware can assign I/O addresses to devices on the PCI bus, thus
 * avoiding the problems associated with hardware jumpers and the like.
 * Applications programmers never, ever, ever need these registers
 * although tools such as device drivers frequently read them.
 *
 * II) PCI Bus Operation Registers; these registers allow the device
 * driver to manage access to the PCI bus by the target device hardware.
 * Again, these registers are of no interest to the applications
 * programmer.
 *
 * III) Reflective Memory Device Registers; these registers access the
 * data sharing and interrupt event management features of the reflective
 * memory product line. Applications programs frequently need these
 * registers.
 *------------------------------------------------------------------------
 * Each group of registers have their definitions below.
 *------------------------------------------------------------------------
 */
/* 
 * Latest version: 3.1
 * Added rfm3rr_pcicmdcode to allow modification of the PCI command codes
 */

/*
 *========================================================================
 * Shape of the PCI Configuration Space Registers
 *========================================================================
 */

#if defined	(LITE9054) // if we are using the PLX 9054LITE prototype board
	#define VENDOR_ID_VMIC		0x10B5	/* PLX's assigned vendor ID */
	#define DEVICE_ID_PMC5565   0x9654  /* PLX 9054 Device ID     */
#elif (PROTO1_5565)    // the PLX Rev AB part boards
	#define VENDOR_ID_VMIC		0x10B5	/* PLX's assigned vendor ID */
	#define DEVICE_ID_PMC5565   0x9656  /* PLX 9656 Device ID     */
#else
	#define VENDOR_ID_VMIC		0x114A	/* VMIC's assigned vendor ID */
	#define DEVICE_ID_PMC5565   0x5565  /* VMIPCI-5565 Device ID     */
#endif
/*
 *========================================================================
 * Shape of the PCI bus operation registers
 *========================================================================
 */

#define RFM_PCIOPREGSIZ (64 * 4)	/* Size of PCI bus oper regs 192 */

typedef struct rfmOpReg_s	{
	union	{
		UCHAR	ror_uc[RFM_PCIOPREGSIZ];
		USHORT	ror_us[RFM_PCIOPREGSIZ/2];
		ULONG	ror_ul[RFM_PCIOPREGSIZ/4];
	}rfmorU;
} rfmOpReg_t, *RFMOR;

/* Convenience macros for accessing parts of the RFM structure		 */

#define rfmor_rorc	rfmorU.ror_uc	/* Registers taken as bytes	     */
#define rfmor_rorw	rfmorU.ror_us	/* Registers taken as words	     */
#define rfmor_rorl	rfmorU.ror_ul	/* Registers taken as longwords	 */


// Registers inside the PLX Tech 9656 used on PMC5565
#define	rfm3rr_pdevvend		rfmor_rorl[0x00/4]	/*  PCI Config space Device Vendor	     */
#define	rfm3rr_cmd			rfmor_rorl[0x04/4]	/*  Command Status	     */
#define rfm2g_bigendian		rfmor_rorc[0x0C]    /* Big/Little Endian config */
#define	rfm3rr_mailbox0	    rfmor_rorl[0x40/4]	/*  mailbox #0		     */
#define	rfm3rr_mailbox1	    rfmor_rorl[0x44/4]	/*  mailbox #1		     */
#define	rfm3rr_mailbox2	    rfmor_rorl[0x48/4]	/*  mailbox #2		     */
#define	rfm3rr_mailbox3	    rfmor_rorl[0x4C/4]	/*  mailbox #3		     */
#define	rfm3rr_mailbox4	    rfmor_rorl[0x50/4]	/*  mailbox #4		     */
#define	rfm3rr_mailbox5	    rfmor_rorl[0x54/4]	/*  mailbox #5		     */
#define	rfm3rr_mailbox6	    rfmor_rorl[0x58/4]	/*  mailbox #6		     */
#define	rfm3rr_mailbox7	    rfmor_rorl[0x5C/4]	/*  mailbox #7		     */
#define	rfm3rr_pcitodoorb	rfmor_rorl[0x60/4]	/*  PCI to Local Doorbell Reg	 */
#define	rfm3rr_loctodoorb	rfmor_rorl[0x64/4]	/*  Local to PCI Doorbell Reg */
#define	rfm3rr_intcsr		rfmor_rorl[0x68/4]	/*  Local Interrupt Control/Status Reg */
#define	rfm3rr_pcicmdcode	rfmor_rorl[0x6C/4]	/*  PCI Command Codes, Serial EEPROM Ctrl, User I/O Ctrl, Init Control */
#define rfm3rr_devvenid		rfmor_rorl[0x70/4]  /*  Device ID and Vendor ID  */
#define rfm3rr_pcihrev		rfmor_rorl[0x74/4]  /*  Revision level of the PLX 9656  */

#define rfm3rr_dmamode0		rfmor_rorl[0x80/4]  /*  DMA Channel 0 Mode   */
#define rfm3rr_dmapadr0		rfmor_rorl[0x84/4]  /*  DMA Channel 0 PCI Address  */
#define rfm3rr_dmaladr0		rfmor_rorl[0x88/4]  /*  DMA CHannel 0 Local Address   */
#define rfm3rr_dmasiz0		rfmor_rorl[0x8C/4]  /*  DMA Channel 0 Transfer Size in bytes  */
#define rfm3rr_dmadpr0		rfmor_rorl[0x90/4]  /*  DMA Channel 0 Descriptor Pointer   */

#define rfm3rr_dmamode1		rfmor_rorl[0x94/4]  /*  DMA Channel 1 Mode   */
#define rfm3rr_dmapadr1		rfmor_rorl[0x98/4]  /*  DMA Channel 1 PCI Address  */
#define rfm3rr_dmaladr1		rfmor_rorl[0x9C/4]  /*  DMA CHannel 1 Local Address   */
#define rfm3rr_dmasiz1		rfmor_rorl[0xA0/4]  /*  DMA Channel 1 Transfer Size in bytes  */
#define rfm3rr_dmadpr1		rfmor_rorl[0xA4/4]  /*  DMA Channel 1 Descriptor Pointer   */
#define rfm3rr_dmacsr0		rfmor_rorc[0xA8]  /*  DMA Channel 0 Command / Status   */

#define rfm3rr_dmaarb		rfmor_rorl[0xAC/4]  /*  DMA Arbitration   */
#define rfm3rr_dmacsr1		rfmor_rorc[0xA9]    /*  DMA Channel 1 Command / Status   */
#define rfm3rr_dmathr		rfmor_rorl[0xBO/4]  /*  DMA Threshold   */
#define rfm3rr_dmahighpadr0		rfmor_rorl[0xB4/4]  /*  DMA Channel 0 PCI High Address  */
#define rfm3rr_dmahighpadr1		rfmor_rorl[0xB8/4]  /*  DMA Channel 1 PCI High Address  */
#define rfm3rr_locAdd1RangeReg		rfmor_rorl[0xf0/4] /* Local Addr Space 1 Range Register */
#define rfm3rr_locAdd1BaseAddr		rfmor_rorl[0xf4/4] /* Local Addr Space 1 Base Address   */

/* Definitions of the rfmor_las1ba register */
#define  RFMOR_LAS1BA_ENABLE_LAS1   (1<<0)  /* Enable Local Address Space 1 */

// PMC5565 boards

/*
 *-----------------------------------------------------------------------------------
 * Shape of the BIGENDian register in the Local Configuration Register space offset 0x0c
 *------------------------------------------------------------------------------------
 */
#define BIGENDIAN_BYTE_LANE			(1<<4) /* Big Endian Byte Lane Mode */
#define PIO_ADDR_SPACE1_BIGENDIAN	(1<<5) /* Direct Slave Address Space 1 Big Endian Mode(Address Invariance) */
#define DMA_CHAN0_BIGENDIAN			(1<<7) /* DMA Channel 0 BIgendian Mode (Address Invariance) */

/*
 *------------------------------------------------------------------------
 * Shape of the  PLX 9656 Interrupt Control / Status register
 *------------------------------------------------------------------------
 */

#define PCI_INT_ENABLED			(1<<8)  /* PCI Interrupt Enable Writing a 1 enables PCI Interrupts */


/*
 *------------------------------------------------------------------------
 * Shape of the RFMOR_LISR Local Interrupt Status Register
 *------------------------------------------------------------------------
 */


#define BIST_INT_ACTIVE				(1<<23) /* BIST (Build In Self Test )Interrupt Active */
#define DMA_CHAN0_ACTIVE			(1<<21) /* DMA Channel 0 Interrupt is active */
#define DMA_CHAN1_ACTIVE			(1<<22) /* DMA Channel 0 Interrupt is active */
#define RFMOR_LISR_AUTO_CLR_INT		(1<<15) /* Auto clear Int. Reading this clears bit 14  */
#define LISR_GLOBAL_INT_EN			(1<<14) /* Global Interrupt Enable */
#define LISR_LOCMEM_PARITYERR		(1<<13) /* Parity error on local memory */
#define RFMOR_LISR_MEM_WRT_INHIBIT	(1<<12) /* Memory write was inhibited. Attemted to do 8 or 16 bit write */
#define LISR_SYNC_LOSS				(1<<11) /* Optical sync signal has been lost - Latched */
#define LISR_RX_FIFO_ISFULL			(1<<10) /* Receive FIFO is full	 */
#define RFMOR_LISR_RX_FIFO_ALMFULL	(1<<9)	/* Receive FIFO is almost full	 */
#define LISR_BADDATA				(1<<8)	/* Receiver has had bad data	 */
#define LISR_PEND_INIT_INT			(1<<7)	/* Pending Initialize Interrupt	 */
#define LISR_ROGUE_PACKET			(1<<6)  /* A rogue (never stopping) packet is on the fibre ring */
#define RFMOR_LISR_RST_NODE_REQ		(1<<3)	/* Reset Node Request */
#define RFMOR_LISR_INT3				(1<<7)  /* Pending Network Interrupt 3	soft(4) */
#define RFMOR_LISR_INT2				(1<<2)  /* Pending Network Interrupt 2	soft(3) */
#define RFMOR_LISR_INT1				(1<<1)  /* Pending Network Interrupt 1	soft(2) */
#define RFMOR_LISR_INT0				(1<<0)  /* Pending Network Interrupt 0  soft(1)	*/
 
 /*
 *------------------------------------------------------------------------
 * Shape of the RFMOR_LIER Local Interrupt Enable Register
 *------------------------------------------------------------------------
 */

#define RFMOR_LIER_AUTO_CLR_INT		(1<<15) /* Auto clear Int  */
#define RFMOR_LIER_LOCMEM_PARITYERR (1<<13) /* Parity error on local memory */
#define RFMOR_LIER_MEM_WRT_INHIBIT	(1<<12) /* Memory write was inhibited. Attemted to do 8 or 16 bit write */
#define LIER_SYNC_LOSS				(1<<11) /* Optical sync signal has been lost - Latched */
#define LIER_RX_FIFO_ISFULL			(1<<10) /* Receive FIFO is full	 */
#define LIER_RX_FIFO_ALMFULL		(1<<9)	/* Receive FIFO is almost full	 */
#define LIER_BADDATA				(1<<8)	/* Receiver has had bad data	 */
#define LIER_PEND_INIT_INT			(1<<7)	/* Pending Initialize Interrupt	 */
#define LIER_ROGUE_PACKET			(1<<6)	/* Enable detection of a rogue (never stopping) packet */
#define LIER_RST_NODE_REQ			(1<<3)	/* Reset Node Request is same as Int 3*/
#define LIER_INT3					(1<<7)  /* Pending Network Interrupt 3	 */
#define LIER_INT2					(1<<2)  /* Pending Network Interrupt 2	 */
#define LIER_INT1					(1<<1)  /* Pending Network Interrupt 1	 */
#define LIER_INT0					(1<<0)  /* Pending Network Interrupt 0	 */

 
 /*
 *------------------------------------------------------------------------
 * Shape of the RFMOR_LCSR1 Local Control and Status Register
 *------------------------------------------------------------------------
 */
#define	RFM_LSCR1_CONFIG_MASK	0x00300000	/* Mask to isolate Mem Config bits 0 & 1 */

#define	LCSR1_LEDON					(1<<31)	/* General Purpose Status LED   */
#define	LCSR1_XMIT_DISABLE			(1<<30)	/* Transmitter Disable    */
#define	LCSR1_DODEN					(1<<29)	/* Dark-on-Dark Enable */
#define	LCSR1_LOOPBACK_EN			(1<<28)	/* Optical disabled, Xmit/Rec Looped back */
#define	LCSR1_LOCPAREN				(1<<27) /* Local bus parity enable	     */

#define	RFMOR_LCSR1_MEMQTY			(2<<20)	/* On board memory amount either 64MB, 128MB with exp to 256MB*/
#define	RFMOR_LCSR1_OFFSET64MB		(2<<16)	/* Offset modulo 64MB 	     */
#define RFMOR_LCSR1_OFFSET0         (1<<16) /* Offset 0 control bit */
#define RFMOR_LCSR1_OFFSET1         (1<<17) /* Offset 1 control bit */

#define	RFMOR_LCSR1_TXFIFOEMPTY		(1<<7)	/* Transmit FIFO is Full */
#define	RFMOR_LCSR1_TXFIFOALMFULL	(1<<6)	/* Transmit FIFO is Almost Full	 */
#define	RFMOR_LCSR1_RXFIFOISFULL	(1<<5)	/* 	Receive FIFO is Full */
#define	RFMOR_LCSR1_RXFIFOALMFULL	(1<<4)	/* Receive FIFO is Almost Full */
#define	LCSR1_SYNCLOSS				(1<<3)	/* Loss of vaild sync signals	 */
#define LCSR1_RXSIGNAL		(1<<2)	/* I see light. Optical receiver is detecting light	*/
#define	LCSR1_BADDATA		(1<<1)	/* Bad data Receiver detected invalid data */
#define	LCSR1_OWNDATA		(1<<0)	/* Our own data has been around the loop	 */

#define RFM2G_PAGE_SIZE		0x1000

/*
 *========================================================================
 * Shape of the reflective memory device registers
 *========================================================================
 */

#define	RFM_REGSIZ	0x40		/* Space reserved for discreet registers */
#define RFM_NOFFSET 0x00

typedef struct rfm_s	{
	union	{
		UCHAR	rfm_uc[RFM_REGSIZ];
		USHORT	rfm_us[RFM_REGSIZ/2];
		ULONG	rfm_ul[RFM_REGSIZ/4];
	} rfmU;
} rfm_t, *RFM, *RFMOPR;

/* Convenience macros for accessing parts of the RFM structure		 */

#define rfm_ram		rfmU.rfm_uc	/* Registers taken as bytes	     */
#define rfm_ramw	rfmU.rfm_us	/* Registers taken as words	     */
#define rfm_raml	rfmU.rfm_ul	/* Registers taken as longwords	 */



// Discreet registers on the PMC5565 2 Gbaud boards 
#define rfm3_rev	rfm_ram[0x00]	 /* Board Revision register (ro)	*/
#define rfm3_bid	rfm_ram[0x01]	 /* Board ID register (ro)	        */
#define rfm3_buildid rfm_ram[0x02]	 /* Board Build ID register (ro)	*/
#define rfm3_nid	rfm_ram[0x04]	 /* Node ID register (ro)	        */
#define rfm3_lcsr1	rfm_raml[0x08/4] /* Local Control & Status Reg #1	*/
#define	rfm3_lisr	rfm_raml[0x10/4] /* Local Interrupt Status Reg #1   */
#define	rfm3_lier	rfm_raml[0x14/4] /* Local Interrupt Enable	        */
#define	rfm3_ntargd	rfm_raml[0x18/4] /* Network Target Data				*/
#define rfm3_ntnode	rfm_ram[0x1C]	 /* Network Target Node				*/
#define	rfm3_nintcmd rfm_ram[0x1D] /* Network Interrupt Command		*/
#define	rfm3_isd1	rfm_raml[0x20/4] /* Interrupt #1 Sender Data        */
#define	rfm3_sid1	rfm_ram[0x24]	 /* Interrupt #1 Sender ID			*/
#define	rfm3_isd2	rfm_raml[0x28/4] /* Interrupt #2 Sender Data        */
#define	rfm3_sid2	rfm_ram[0x2C]	 /* Interrupt #2 Sender ID			*/
#define	rfm3_isd3	rfm_raml[0x30/4] /* Interrupt #3 Sender Data        */
#define	rfm3_sid3	rfm_ram[0x34]	 /* Interrupt #3 Sender ID			*/
#define rfm3_initNodedata	rfm_raml[0x38/4]  /* 	    */
#define	rfm3_initNodeID	rfm_ram[0x3C]	/* Initialize Node ID			*/
#define rfm3_isd4	rfm3_initNodedata  /* same as 0x38 */
#define	rfm3_sid4	rfm3_initNodeID    /* same as 0x3c*/
/*
 *------------------------------------------------------------------------
 * Shape of the RFM_BID (board ID) register
 *------------------------------------------------------------------------
 */

#define RFM_BID_PMC5565		0x65		/* VMIPMC-5565  */

/*
 *------------------------------------------------------------------------
 * Shape of the RFM_IRS (interrupt and receiver) register
 *------------------------------------------------------------------------
 */

// #define RFM_IRS_RSYNC		(1<<7)	/* 5565: Receiver sync'ed (low)	 */
// #define	RFM_IRS_LSYNCLOSS	(1<<6)	/* 5565: Latched sync loss	     */
// #define	RFM_IRS_BADDATA		(1<<5)	/* Bad data received		     */
// #define	RFM_IRS_RXFIFO		(1<<4)	/* Receiver FIFO half full (low) */


/*
 *------------------------------------------------------------------------
 * Shape of the LISR  register
 *------------------------------------------------------------------------
 */

#define	RFM_LISR_FIFOFULL	(1<<10)  /* Receive FIFO is FULL */
#define	RFM_LISR_BADDATA	(1<<8)  /* BAD DATA  */
#define	RFM_LISR_INT4		(1<<7)	/* INT4 pending	     */
#define	RFM_LISR_ROGUEPKT	(1<<6)  /* Rogue Packet */
#define	RFM_LISR_RESET		(1<<3)	/* Node reset received		     */
#define	RFM_LISR_INT3		(1<<2)	/* INT3 pending			         */
#define	RFM_LISR_INT2		(1<<1)	/* INT2 pending			         */
#define	RFM_LISR_INT1		(1<<0)	/* INT1 pending			         */

#define LCSR1_CONFIG_SHIFT		(2 << 20)
#define RFM_LCSR1_CONFIG_64M	0x00000000
#define RFM_LCSR1_CONFIG_128M	0x00100000
#define RFM_LCSR1_CONFIG_256M   0x00200000

/*
 *------------------------------------------------------------------------
 * Shape of the RFM_CMD (command register)
 *------------------------------------------------------------------------
 */

#define	RFM_CMD_ALL		    (1<<3)	/* Global enable Broadcast to all nodes regardless of NTN */
#define	RFM_CMD_OWN_PACKET  (1<<2)	/* Send Frame Packet  so as to set OWN_DATA. For ring cont test */

/*
 * Macro definition for defining IOCTL and FSCTL function control codes.  Note
 * that function codes 0-2047 are reserved for Microsoft Corporation, and
 * 2048-4095 are reserved for customers.
 */

#define PCI55XX_IOCTL_BASE  0x0800

/*
 *========================================================================
 * Define the PCI55XX IOCTL's.
 *========================================================================
 */


/*
 *========================================================================
 * The following definitions relate to the applications program interface
 * (API) for allowing I/O control commands.
 *========================================================================
 */

/*
 * Define the various device type values.  Note that values used by Microsoft
 * Corporation are in the range 0-32767, and 32768-65535 are reserved for use
 * by customers.
 */

#define FILE_DEVICE_PCI5565  0xD565	/* Binary 0x5565 with MSB set	 */

/*
 *------------------------------------------------------------------------
 * The _IOCTL_PCI55XX_NNN() macro defines a tool to construct the
 * individual ioctl commands.  Each "offset" must uniquely identify the
 * ioctl command.
 *------------------------------------------------------------------------
 */

#define IOCTL_PCI55XX_NNN(offset, method, access) \
    	CTL_CODE(FILE_DEVICE_PCI5565, (PCI55XX_IOCTL_BASE+offset), method, access)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_MAP_RFM command maps the entire reflective memory
 * contents into the applications program. It takes no input arguments.
 * The output argument must be a "rfmMapMemory_t" structure which the
 * driver fills out.
 *------------------------------------------------------------------------
 */

typedef struct	rfmMapMemory_s	{
	RFM	rmm_rfm;		        /* Mapped address of RFM	     */
	ULONG	rmm_size;		    /* Total size of the mapped area */
	ULONG	rmm_freeFireZone;	/* Offset of first user location */
} rfmMapMemory_t, *RFMMAPMEMORY;

/*  */
typedef struct	rfmOPRegMap_s	{
	RFMOPR	rmmopr_rfm;		    /* Mapped address of RFM	     */
	ULONG	rmmopr_size;		/* Total size of discreet opreational reg area */
	ULONG	rmmopr_freeFireZone;	/* Offset of first user location */
} rfmOPMap_t, *RFMOPREGMAPMEMORY;


#define IOCTL_PCI55XX_MAP_RFM \
    IOCTL_PCI55XX_NNN(0, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_UNMAP_RFM command unmaps the entire reflective memory
 * contents from the applications program. The input argument must be the
 * structure filled in by the IOCTL_PCI55XX_MAP_RFM command. There is no
 * output argument.
 *------------------------------------------------------------------------
 */

#define IOCTL_PCI55XX_UNMAP_RFM \
    IOCTL_PCI55XX_NNN(1, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_SEND_INTERRUPT command transmits the named RFM
 * interrupt event to the specified RFM node (or to all RFM nodes). The
 * input argument must be a rfmSendEvent_t structure. There is no output
 * argument. It is always an error to attempt to send an interrupt to
 * one's own node.
 *------------------------------------------------------------------------
 * The IOCTL_INTERNAL_PCI55XX_SEND_INTERRUPT command is for VMIC use only.
 * User application programs should not attempt to use this function.
 *------------------------------------------------------------------------
 */

typedef struct rfmSendEvent_s	{
	USHORT		rse_destNode;	/* Target node number		 */
#define	RFM_RSE_BROADCAST	0xFFFF	/* Send to all nodes		 */
	USHORT		rse_eventId;	/* Send RFM2GEVENT_ 1,2,3	 */
	ULONG		rse_userData;   /* users data to send, ends up in the receive nodes ISD FIFO */
} rfmSendEvent_t, *RFMSENDEVENT;

#define IOCTL_PCI55XX_SEND_EVENT \
    IOCTL_PCI55XX_NNN(2, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_PCI55XX_SEND_EVENT \
    IOCTL_PCI55XX_NNN(1302, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_GET_NEVENTS command returns the number of times each
 * event has occurred. The input argument is a ULONG; if its value is
 * nonzero, the counters are cleared after they are returned. The output
 * arguments must be a rfmGetNevents_t structure.
 *------------------------------------------------------------------------
 */

typedef struct	rfmGetNevents_s	{
	ULONG		rge_nEvents[RFM2GEVENT_LAST];   /* RFM ireq	*/
	ULONG		rge_nDma;	    /* Number of DMA operations	    */
	ULONG		rge_nDmaErr;	/* Number of DMA errors		    */
} rfmGetNevents_t, *RFMGETNEVENTS;

#define	IOCTL_PCI55XX_GET_NEVENTS	\
    IOCTL_PCI55XX_NNN(3, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_EVENT_NOTIFY command returns only when the indicated
 * RFM interrupt event occurs. Both the input and output arguments must be
 * an rfmEventNotify_t strucuture.  The "ren_eventId" element identifies
 * the RFM interrupt event to await; The "ren_nEvent" element is an
 * ordinal number indicating which event instance was detected.  If two
 * sequential IOCTL_PCI55XX_EVENT_NOTIFY commands for the same event
 * return "ren_nEvent" which differ by more than 1 unit, then there 
 * have been "n-m" events missed by the application.  See the
 * IOCTL_PCI55XX_GET_NEVENTS command for more information about event
 * counts.
 *------------------------------------------------------------------------
 */

typedef struct rfmEventNotify_s	{
	USHORT		ren_eventId;	/* IN: RFM Event ID to notify	 */
	ULONG		ren_nEvent;	    /* OUT: Event instance number	 */
	UCHAR		ren_senderId;	/* OUT: RFM Node sending event	 */
	ULONG		ren_userdata;	/* IN: Userdata from hardware FIFO */
} rfmEventNotify_t, *RFMEVENTNOTIFY;

#define	IOCTL_PCI55XX_EVENT_NOTIFY	\
    IOCTL_PCI55XX_NNN(4, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_GET_DEBUG_FLAGS command returns the current device
 * driver debug flags, while the IOCTL_PCI55XX_NEW_DEBUG_FLAGS command
 * changes them. To get the appropriate debug flag value and name, use the
 * IOCTL_PCI55XX_DEBUG_FLAG_NAME command.
 *------------------------------------------------------------------------
 * NOTICE: The names and associated mask bit definitions are not
 * guaranteed to be consistant from one release of the driver to another.
 * Flags may be added and flags may be removed. No application program
 * should depend on the presence of any particular debug flag for its
 * correct operation.  Since these flags are intended for VMIC's use in
 * resolving problems with the device driver, it is recommended that user
 * applications programs make *NO* use of these values unless specificly
 * directed by VMIC.
 *------------------------------------------------------------------------
 */

typedef struct	rfmDebugFlagName_s	{
	ULONG		rdfn_bitno;	    /* Binary bit number		    */
	ULONG		rdfn_mask;	    /* Binary mask value		    */
	char		rdfn_name[16];	/* ASCII flag name w/final null */
} rfm2gDebugFlagName_t, *RFM2GDEBUGFLAGNAME;

#define	IOCTL_PCI55XX_GET_DEBUG_FLAGS	\
    IOCTL_PCI55XX_NNN(5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define	IOCTL_PCI55XX_NEW_DEBUG_FLAGS	\
    IOCTL_PCI55XX_NNN(6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define	IOCTL_PCI55XX_DEBUG_FLAG_NAME	\
    IOCTL_PCI55XX_NNN(7, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_NEW_DMA_THRESHOLD command establishes a new minimum
 * length for a read/write transfer below which DMA will not be
 * considered. The IOCTL_PCI55XX_GET_DMA_THRESHOLD returns the current
 * setting.  Both commands require a ULONG paramter.
 *------------------------------------------------------------------------
 */

#define	IOCTL_PCI55XX_GET_DMA_THRESHOLD	\
    IOCTL_PCI55XX_NNN(8, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define	IOCTL_PCI55XX_NEW_DMA_THRESHOLD	\
    IOCTL_PCI55XX_NNN(9, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_GET_CONFIG command returns interesting information
 * about the RFM device. The output argument must be an rfmGetConfig_t
 * structure.
 *------------------------------------------------------------------------
 */

typedef struct rfmGetConfig_s	{
	UCHAR	rgc_boardId;		/* VMIC board ID		         */
	UCHAR	rgc_nodeId;		    /* RFM network node ID		     */
	ULONG	rgc_registerSize;	/* Bytes consumed by registers	 */
	ULONG	rgc_memorySize;		/* Amount of RAM memory on board */
	ULONG	rgc_pciWindowLen;	/* Size of requested PCI window	 */
	ULONG	rgc_freeFireZone;	/* Beginning of available RAM	 */
	char	rgc_product[32];	/* VMIC Product Name "VMISFT-RFM2G-ABC-DEF" was 64 bytes	*/
	char	rgc_driverVersion[16];	/* Device driver version string was 64 bytes */
	ULONG	rgc_maxQueueSize;	/* Maximum Event Queue Size      */
	char    rgc_plxchiprev;		/* Revision number of the PLX 9656 PCI interface */
    RFM2GPCICONFIG rgc_pciConfig;   /* PCI Bus Specific Info     */
	char rgc_boardRev;
	char rgc_buildid;


} rfmGetConfig_t, *RFMGETCONFIG;


#define	IOCTL_PCI55XX_GET_CONFIG	\
    IOCTL_PCI55XX_NNN(10, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_GET_QUEUE_COUNT command returns the number of 
 * events in the specified queue. If RFM2GEVENT_LAST is passed,
 * the count of all queues is returned. The input is a long with the
 * queue ID number. The output is the number of elements, also a long
 *------------------------------------------------------------------------
 */

#define	IOCTL_PCI55XX_GET_QUEUE_COUNT	\
    IOCTL_PCI55XX_NNN(11, METHOD_BUFFERED, FILE_ANY_ACCESS)


/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_FLUSH_QUEUE command returns the number of events
 * flushed from the specified queue. If RFM2GEVENT_LAST is passed,
 * the all queues are flushed. The input is a long with the
 * queue ID number. The output is the number of elements, also a long
 *------------------------------------------------------------------------
 */

#define	IOCTL_PCI55XX_FLUSH_QUEUE	\
    IOCTL_PCI55XX_NNN(12, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_QUEUED_EVENT_NOTIFY is identical in function to the
 * EVENT NOTIFY IOCTL call, except it also uses a queue to hold past,
 * unanswered events.
 *------------------------------------------------------------------------
 */

#define	IOCTL_PCI55XX_QUEUED_EVENT_NOTIFY	\
    IOCTL_PCI55XX_NNN(13, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 * Map the Discreet 5565 registers
 */
#define IOCTL_PCI55XX_MAP_REGS_RFM \
    IOCTL_PCI55XX_NNN(14, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 *------------------------------------------------------------------------
 * The IOCTL_PCI55XX_UNMAP_REGS_RFM command unmaps the 5565 Discreet Registers
 * contents from the applications program. The input argument must be the
 * structure filled in by the IOCTL_PCI55XX_MAP_REGS_RFM command. There is no
 * output argument.
 *------------------------------------------------------------------------
 */

#define IOCTL_PCI55XX_UNMAP_REGS_RFM \
    IOCTL_PCI55XX_NNN(15, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 * Enable the reflective memory interrupts
 */
#define IOCTL_PMC5565_EVENT_ENABLE_RFM2G \
    IOCTL_PCI55XX_NNN(16, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 * Disable the reflective memory interrupts
 */

#define IOCTL_PMC5565_EVENT_DISABLE_RFM2G \
    IOCTL_PCI55XX_NNN(17, METHOD_BUFFERED, FILE_ANY_ACCESS)


/*
 * Check the reflective memory fibre loop for continuity
 */

#define IOCTL_PMC5565_CHECK_RING_CONT \
    IOCTL_PCI55XX_NNN(18, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 * Cancel an outstanding request for an Event notification interrupt Not currently used
 */

#define IOCTL_PMC5565_CANCEL_EVENT \
    IOCTL_PCI55XX_NNN(19, METHOD_BUFFERED, FILE_ANY_ACCESS)

/* 
 * Set the Byteswap logic in the PLX 9656 chip for use on PIO accesses
 */
#define IOCTL_PMC5565_SET_PIO_BYTESWAP \
    IOCTL_PCI55XX_NNN(20, METHOD_BUFFERED, FILE_ANY_ACCESS)
/* 
 * Get the state of the Byteswap logic in the PLX 9656 chip for use on PIO accesses
 */
#define IOCTL_PMC5565_GET_PIO_BYTESWAP \
    IOCTL_PCI55XX_NNN(21, METHOD_BUFFERED, FILE_ANY_ACCESS)

/* 
 * Set the Byteswap logic in the PLX 9656 chip for use on DMA accesses
 */
#define IOCTL_PMC5565_SET_DMA_BYTESWAP \
    IOCTL_PCI55XX_NNN(22, METHOD_BUFFERED, FILE_ANY_ACCESS)

 /* 
 * Enable the Byteswap logic in the PLX 9656 chip for use on DMA accesses
 */
#define IOCTL_PMC5565_GET_DMA_BYTESWAP \
    IOCTL_PCI55XX_NNN(23, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
 * Map the PLX registers
 */
#define IOCTL_PCI55XX_MAP_REGS_PLX \
    IOCTL_PCI55XX_NNN(24, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PCI55XX_UNMAP_REGS_PLX \
    IOCTL_PCI55XX_NNN(25, METHOD_BUFFERED, FILE_ANY_ACCESS)

/**************************************************************************
*	Set/Clr RFM/PLX registers
**************************************************************************/
#define IOCTL_PCI55XX_MASK_REG_RFM \
    IOCTL_PCI55XX_NNN(27, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PCI55XX_MASK_REG_PLX \
    IOCTL_PCI55XX_NNN(28, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PCI55XX_MASK_REG_MEM \
    IOCTL_PCI55XX_NNN(29, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef	struct
{
	ULONG	RegOff;
	ULONG	RegWid;
	ULONG	SetMask;
	ULONG	ClrMask;
} MASK_REG_IN;


#define IOCTL_PCI55XX_DRIVER_INFO \
    IOCTL_PCI55XX_NNN(30, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef	struct
{
	ULONG	bReset;
	ULONG	DmaDispCnt;
	ULONG	DmaStrtCnt;
	ULONG	DmaRdTot;
	ULONG	DmaWrTot;
	ULONG	EvtSndCnt[RFM2GEVENT_LAST];
	ULONG	EvtRcvCnt[RFM2GEVENT_LAST];
}
DRIVER_INFO;

#define IOCTL_PCI55XX_WRITE_REG_RFM \
    IOCTL_PCI55XX_NNN(31, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PCI55XX_WRITE_REG_PLX \
    IOCTL_PCI55XX_NNN(32, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PCI55XX_WRITE_REG_MEM \
    IOCTL_PCI55XX_NNN(33, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef	struct
{
	ULONG	RegOff;
	ULONG	RegWid;
	ULONG	WriteValue;
} WRITE_REG;

#define IOCTL_PCI55XX_SET_SLIDING_WINDOW \
    IOCTL_PCI55XX_NNN(34, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef	struct
{
	ULONG	SlidingWindowOffset;
	ULONG	SlidingWindowOffsetEnable;
} SLIDING_WINDOW_SET;
#endif



