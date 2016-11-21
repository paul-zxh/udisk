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

#include "stdint.h"
#include "j32xx.h"
#include "usb.h"
#include "nflash.h"
#include "ahb_usbnfc.h"



#ifdef JTAG_PRINT_SUPPORT
#include "jtag_con.h"
#endif

int main(void)
{
    DSU_CTRL_REG = 0x1c6;
    GPIO_ICS_REG = 0x387;
    GPIO_GCC_REG = 0xffff;

    volatile int *ahbcswc_ctr_reg = (volatile unsigned int *)0x12000000;
    ahbcswc_ctr_reg[0]=(46<<25)|0x402ff;

    eflash_init();
    
    NFC_Flash_Init(NFC_FACE_MODE,NFC_SPEED_MODE);

    usb_init();

    irqmp_init(IRQMP_LEVEL_USB);
    irqmp_enable_gmask();

    while (1) {
        if (!usb_irq_flag) {
            continue;
        }

        if (usb_irq_flag == IRQMP_LEVEL_USB_CRYPTO) {
            if (usb_irq_stat & USB_CPT_IRQ_EP3) {
                usb_bk_out();
            }
        }
        
        else if (usb_irq_flag == IRQMP_LEVEL_USB_DEVICE) {
            usb_dev_dsr();
        }
        
        else if (usb_irq_flag == IRQMP_LEVEL_USB_NFC) {
            NFC_handler();
        }

        usb_irq_stat = 0;
        usb_irq_flag = 0;
        
        irqmp_enable_usb();
    }

    return 0x55aaaa55;
}

void Isr_Handler(uint32_t irq_level, uint32_t reserve)
{
    switch (irq_level) {

        case IRQMP_LEVEL_USB_NFC:
            nfcIrqStat = nfcReg->intr_src_clr;
            nfcReg->intr_src_clr |= nfcIrqStat;
            usb_irq_flag = IRQMP_LEVEL_USB_NFC;
            irqmp_disable_usb();
            break;
        
        case IRQMP_LEVEL_USB_CRYPTO:
            usb_irq_stat = pUsbCptReg->irqStat;
            pUsbCptReg->irqStat = usb_irq_stat;
            if (epOutMask == 1) {
                usb_irq_flag = IRQMP_LEVEL_USB_CRYPTO;
                irqmp_disable_usb();
            }
            break;
        
        case IRQMP_LEVEL_USB_DEVICE:
            usb_irq_stat = pUsbDevReg->irqm.irqStatL;
            if (usb_irq_stat & pUsbDevReg->irqm.irqEnbL) {
                pUsbDevReg->irqm.irqStatL = usb_irq_stat;  // clearing the irq_status registers
                usb_irq_flag = IRQMP_LEVEL_USB_DEVICE;
                irqmp_disable_usb();
            }
            break;

        default:
            break;
    }

    IRQMP_ICLEAR_REG = (1 << irq_level);
}

