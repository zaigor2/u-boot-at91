/*
 * Configuation settings for Emerson iPro4 board
 *
 * (C) Copyright 2017 Emerson
 * (C) Copyright 2017 Rodolfo Giometti <giometti@enneenne.com>
 * 
 * Based on at91sam9260ek.h from Atmel
 *
 * Original copyright message:
 *
 * (C) Copyright 2007-2008
 * Stelian Pop <stelian@popies.net>
 * Lead Tech Design <www.leadtechdesign.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * SoC must be defined first, before hardware.h is included.
 * In this case SoC is defined in boards.cfg.
 */
#include <asm/hardware.h>

/*
 * Warning: changing CONFIG_SYS_TEXT_BASE requires
 * adapting the initial boot program.
 * Since the linker has to swallow that define, we must use a pure
 * hex number here!
 */
#define CONFIG_SYS_TEXT_BASE		0x21f00000

/* ARM asynchronous clock */
#define CONFIG_SYS_AT91_SLOW_CLOCK	32768		/* slow clock xtal */
#define CONFIG_SYS_AT91_MAIN_CLOCK	18432000	/* main clock xtal */

/* Define actual evaluation board type from used processor type */
#define CONFIG_IPRO4

/* Misc CPU related */
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_SKIP_LOWLEVEL_INIT

/* general purpose I/O */
#define CONFIG_ATMEL_LEGACY		/* required until (g)pio is fixed */

/* serial console */
#define CONFIG_BAUDRATE			115200

/* hardware watchdog */
#define CONFIG_HW_WATCHDOG		1
#define CONFIG_HW_WATCHDOG_PIN		AT91_PIN_PC4

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE	1
#define CONFIG_BOOTP_BOOTPATH		1
#define CONFIG_BOOTP_GATEWAY		1
#define CONFIG_BOOTP_HOSTNAME		1

/*
 * Command line configuration.
 */
#define CONFIG_CMD_NAND		1

/*
 * SDRAM: 1 bank, min 32, max 128 MB
 * Initialized before u-boot gets started.
 */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		ATMEL_BASE_CS1
#define CONFIG_SYS_SDRAM_SIZE		0x04000000

/*
 * Initial stack pointer: 4k - GENERATED_GBL_DATA_SIZE in internal SRAM,
 * leaving the correct space for initial global data structure above
 * that address while providing maximum stack area below.
 */
#ifdef CONFIG_AT91SAM9XE
# define CONFIG_SYS_INIT_SP_ADDR \
	(ATMEL_BASE_SRAM + 16 * 1024 - GENERATED_GBL_DATA_SIZE)
#else
# define CONFIG_SYS_INIT_SP_ADDR \
	(ATMEL_BASE_SRAM1 + 16 * 1024 - GENERATED_GBL_DATA_SIZE)
#endif

/*
 * The (arm)linux board id set by generic code depending on configured board
 * (see boards.cfg for different boards)
 */
#define CONFIG_MACH_TYPE MACH_TYPE_AT91SAM9260EK

/* DataFlash */
#define CONFIG_ATMEL_DATAFLASH_SPI
#define CONFIG_HAS_DATAFLASH		1
#define CONFIG_SYS_MAX_DATAFLASH_BANKS		2
#define CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0	0xC0000000	/* CS0 */
#define CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS1	0xD0000000	/* CS1 */
#define AT91_SPI_CLK			15000000

#ifdef CONFIG_AT91SAM9G20EK
#define DATAFLASH_TCSS			(0x22 << 16)
#else
#define DATAFLASH_TCSS			(0x1a << 16)
#endif
#define DATAFLASH_TCHS			(0x1 << 24)

/* NAND flash */
#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_ATMEL
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		ATMEL_BASE_CS3
#define CONFIG_SYS_NAND_DBW_8
#define CONFIG_SYS_NAND_MASK_ALE	(1 << 21)
#define CONFIG_SYS_NAND_MASK_CLE	(1 << 22)
#define CONFIG_SYS_NAND_ENABLE_PIN	AT91_PIN_PC14
#define CONFIG_SYS_NAND_WRITE_PIN	AT91_PIN_PC5
#define CONFIG_SYS_NAND_READY_PIN	AT91_PIN_PC13
#endif

/* USB */
#define CONFIG_USB_ATMEL
#define CONFIG_USB_ATMEL_CLK_SEL_PLLB
#define CONFIG_USB_OHCI_NEW		1
#define CONFIG_SYS_USB_OHCI_CPU_INIT		1
#define CONFIG_SYS_USB_OHCI_REGS_BASE		0x00500000	/* AT91SAM9260_UHP_BASE */
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"at91sam9260"
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	2

#define CONFIG_SYS_LOAD_ADDR			0x22000000	/* load address */

#define CONFIG_SYS_MEMTEST_START		CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END			0x23e00000

#ifdef CONFIG_SYS_USE_DATAFLASH_CS0

/* bootstrap + u-boot + env + linux in dataflash on CS0 */
#define CONFIG_ENV_IS_IN_DATAFLASH	1
#define CONFIG_SYS_MONITOR_BASE	(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0 + 0x8400)
#define CONFIG_ENV_OFFSET		0x4200
#define CONFIG_ENV_ADDR		(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS0 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		0x4200
#define CONFIG_BOOTCOMMAND	"cp.b 0xC0084000 0x22000000 0x210000; bootm"
#define CONFIG_BOOTARGS		"console=ttyS0,115200 "			\
				"root=/dev/mtdblock0 "			\
				"mtdparts=atmel_nand:-(root) "		\
				"rw rootfstype=jffs2"

#elif CONFIG_SYS_USE_DATAFLASH_CS1

/* bootstrap + u-boot + env + linux in dataflash on CS1 */
#define CONFIG_ENV_IS_IN_DATAFLASH	1
#define CONFIG_SYS_MONITOR_BASE	(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS1 + 0x8400)
#define CONFIG_ENV_OFFSET		0x4200
#define CONFIG_ENV_ADDR		(CONFIG_SYS_DATAFLASH_LOGIC_ADDR_CS1 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		0x4200
#define CONFIG_BOOTCOMMAND	"cp.b 0xD0084000 0x22000000 0x210000; bootm"
#define CONFIG_BOOTARGS		"console=ttyS0,115200 "			\
				"root=/dev/mtdblock0 "			\
				"mtdparts=atmel_nand:-(root) "		\
				"rw rootfstype=jffs2"

#elif defined(CONFIG_SYS_USE_NANDFLASH)

/* bootstrap + u-boot + env + linux in nandflash */
#define CONFIG_ENV_IS_IN_NAND	1
#define CONFIG_ENV_OFFSET		0xA0000
#define CONFIG_ENV_OFFSET_REDUND	0xC0000
#define CONFIG_ENV_SIZE		0x20000		/* 1 sector = 128 kB */
#define CONFIG_BOOTCOMMAND	"run usbboot ; run setroma ; "		\
				"nand read 0x21000000 "			\
					"$kernel_address 0xA00000; "	\
				"bootm 0x21000000"
#define CONFIG_BOOTARGS							\
	"console=ttyS0,115200 earlyprintk "
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"usbboot=run usbargs ; "					\
		"mw 0x21000000 a ; run usbload ; bootm 0x21000000\0"	\
	"usbargs=setenv bootargs rdinit=/linuxrc "			\
		"mem=64M usbboot console=ttyS0,115200 $platform_info "	\
		"rootfs_partition=$rootfs_partition "			\
		"kernel_partition=$kernel_partition\0"			\
	"setroma=setenv bootargs mem=64M console=ttyS0,115200 "		\
		"ubi.mtd=$rootfs_mtd root=ubi0:root rw "		\
		"rootfstype=ubifs $platform_info\0"			\
	"usbload=usb reset; fatload usb 0 0x21000000 edsboot; usb stop\0"\
	"rootfs_mtd=7\0"						\
	"kernel_address=0x100000\0"					\
	"platform_info=hw=ipl rev=1\0"					\
	"rootfs_partition=1\0"						\
	"kernel_partition=1\0"

#else	/* CONFIG_SYS_USE_MMC */
/* bootstrap + u-boot + env + linux in mmc */
#define CONFIG_ENV_IS_IN_MMC
/* For FAT system, most cases it should be in the reserved sector */
#define CONFIG_ENV_OFFSET		0x2000
#define CONFIG_ENV_SIZE			0x1000
#define CONFIG_SYS_MMC_ENV_DEV		0

#define CONFIG_BOOTCOMMAND						\
	"fatload mmc 0:1 0x22000000 uImage; bootm"
#define CONFIG_BOOTARGS							\
	"console=ttyS0,115200 earlyprintk "				\
	"mtdparts=atmel_nand:256k(bootstrap)ro,512k(uboot)ro,"		\
	"256k(env),256k(env_redundant),256k(spare),"			\
	"512k(dtb),6M(kernel)ro,-(rootfs) "				\
	"root=/dev/mmcblk0p2 rw rootfstype=ext4 rootwait"
#endif

#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_LONGHELP		1
#define CONFIG_CMDLINE_EDITING	1
#define CONFIG_AUTO_COMPLETE

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		ROUND(3 * CONFIG_ENV_SIZE + 128*1024, 0x1000)

#endif
