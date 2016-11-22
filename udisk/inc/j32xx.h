/*
********************************************************************************
********************************************************************************
*
*                       Copyright (c) 2016, JETWAY, WuHan
*                              All Rights Reserved.
*
********************************************************************************
********************************************************************************
*/

#ifndef _J32XX_H
#define _J32XX_H

#define __crypt


// ���������ض���
typedef char                    CHAR;
typedef unsigned char           BOOL;
typedef unsigned char           bool;
typedef unsigned char           BYTE;
//typedef unsigned char           uint8_t;
typedef signed char             INT8S;
//typedef unsigned short          uint16_t;
typedef signed short            INT16S;
//typedef unsigned int            uint32_t;
typedef signed int              INT32S;
typedef long long               INT64U;
typedef float                   FP32;
typedef double                  FP64;
typedef volatile unsigned char  VINT8U;
typedef volatile unsigned int   VINT32U;
typedef volatile signed int     VINT32S;

#define IN
#define OUT
#define IN_OUT

#define TRUE    1
#define true    1
#define FALSE   0
#define false   0
#define NULL    (void *)0

#define LOINT16U(l)     ((uint16_t)(l))
#define HIINT16U(l)     ((uint16_t)(((uint32_t)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)       ((BYTE)(w))
#define HIBYTE(w)       ((BYTE)(((uint16_t)(w) >> 8) & 0xFF))
#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))
#define ILTOBENDIAN(X)  ((((X)>>24)&0xff) | (((X)>>8)&0xff00) | (((X)<<8)&0xff0000) | \
                         (((X)<<24)&0xff000000))
#define WLTOBENDIAN(X)  ((((X)>>8)&0xff) | (((X)<<8)&0xff00))



#define DSU_BASE_ADDR           0x90000000 // -0x9fffffff 
#define DSU_CTRL_REG            (*(VINT32U*)(DSU_BASE_ADDR + 0x00))

#define GPIO_BASE_ADDR          (0x08000500)
#define GPIO_inData_REG         (*(VINT32U*)(GPIO_BASE_ADDR + 0x00))
#define GPIO_outData_REG        (*(VINT32U*)(GPIO_BASE_ADDR + 0x04))
#define GPIO_dirCtl_REG         (*(VINT32U*)(GPIO_BASE_ADDR + 0x08))
#define GPIO_intMask_REG        (*(VINT32U*)(GPIO_BASE_ADDR + 0x0C))
#define GPIO_intPolarity_REG    (*(VINT32U*)(GPIO_BASE_ADDR + 0x10))
#define GPIO_intEdge_REG        (*(VINT32U*)(GPIO_BASE_ADDR + 0x14))
#define GPIO_pullUp_REG         (*(VINT32U*)(GPIO_BASE_ADDR + 0x18)) 
#define GPIO_auxiliaryOut_REG   (*(VINT32U*)(GPIO_BASE_ADDR + 0x1C)) 
#define GPIO_ICS_REG            (*(VINT32U*)(GPIO_BASE_ADDR + 0x20))
#define GPIO_GCC_REG            (*(VINT32U*)(GPIO_BASE_ADDR + 0x24))
#define GPIO_PCONFIG_REG        (*(VINT32U*)(GPIO_BASE_ADDR + 0x28))
#define GPIO_CONSADDR_REG       (*(VINT32U*)(GPIO_BASE_ADDR + 0x3c))



#define IRQMP_BASE_ADDR         0x08000200 // -0x080002ff
#define IRQMP_IPRI_REG          (*(VINT32U*)(IRQMP_BASE_ADDR + 0x00)) // �ж����ȼ��Ĵ���
#define IRQMP_IUNSETTLED_REG    (*(VINT32U*)(IRQMP_BASE_ADDR + 0x04)) // δ�����жϼĴ���
#define IRQMP_IFORCE_REG        (*(VINT32U*)(IRQMP_BASE_ADDR + 0x08)) // ǿ���жϼĴ���
#define IRQMP_ISTATE_REG        (*(VINT32U*)(IRQMP_BASE_ADDR + 0x10)) // �ദ����״̬�Ĵ���
#define IRQMP_ICLEAR_REG        (*(VINT32U*)(IRQMP_BASE_ADDR + 0x0c)) // �ж�����Ĵ���
#define IRQMP_GMASK_REG         (*(VINT32U*)(IRQMP_BASE_ADDR + 0x18)) // �������ж������μĴ���
#define IRQMP_IMASK_REG         (*(VINT32U*)(IRQMP_BASE_ADDR + 0x40)) // �������ж����μĴ���

#define IRQMP_LEVEL_I2C1        1
#define IRQMP_LEVEL_I2C2        2
#define IRQMP_LEVEL_SHA1        4
#define IRQMP_LEVEL_SCH         5
#define IRQMP_LEVEL_SMS4        6
#define IRQMP_LEVEL_TRNG        7
#define IRQMP_LEVEL_CLUE        8
#define IRQMP_LEVEL_UART        9
#define IRQMP_LEVEL_TCMC        10
#define IRQMP_LEVEL_TIMER       11
#define IRQMP_LEVEL_EFM         12
#define IRQMP_LEVEL_GPIO        13
#define IRQMP_LEVEL_7816        14

#define IRQMP_LEVEL_USB_DEVICE      4
#define IRQMP_LEVEL_USB_NFC         5
#define IRQMP_LEVEL_USB_CRYPTO      6
#define IRQMP_LEVEL_USB             0x70

#define IRQMP_LEVEL_NULL            0xff


#define irqmp_init(irq)             IRQMP_IMASK_REG = irq
#define irqmp_enable(irq)           IRQMP_IMASK_REG |= (1 << irq)
#define irqmp_disable(irq)          IRQMP_IMASK_REG &= ~(1 << irq)
#define irqmp_clear(irq)            IRQMP_ICLEAR_REG = (1 << irq)
#define irqmp_enable_gmask()        IRQMP_GMASK_REG = 1
#define irqmp_disable_gmask()       IRQMP_GMASK_REG = 0
#define irqmp_enable_usb()          IRQMP_IMASK_REG |= 0x70
#define irqmp_disable_usb()         IRQMP_IMASK_REG &= ~(0x70)

//#define JTAG_PRINT_SUPPORT
#define jprintf(fmt, ...)  do {} while (0)


#endif

