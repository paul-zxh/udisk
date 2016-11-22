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

#ifndef _EFLASH_H
#define _EFLASH_H

#define EFLASH_BASE (0x08000a00)


/* AHBEF32KX32C �Ĵ����� */

// ʱ������Ĵ��� 1
#define EFLASH_TIMER1_REG       (*(VINT32U*)(EFLASH_BASE + 0x00))

// ʱ������Ĵ��� 2
#define EFLASH_TIMER2_REG       (*(VINT32U*)(EFLASH_BASE + 0x04))

// ʱ������Ĵ��� 3
#define EFLASH_TIMER3_REG       (*(VINT32U*)(EFLASH_BASE + 0x08))

// ʱ������Ĵ��� 4
#define EFLASH_TIMER4_REG       (*(VINT32U*)(EFLASH_BASE + 0x0c))

// ���ƼĴ��� 1
#define EFLASH_CTRL1_REG        (*(VINT32U*)(EFLASH_BASE + 0x10))

// ���ƼĴ��� 2
#define EFLASH_CTRL2_REG        (*(VINT32U*)(EFLASH_BASE + 0x14))


#define Fsysclk         35

#define Terase          22              //20000us//20ms
#define Txa             35              //35ns          <----------------ns
#define Tnvh            5               //5us
#define Tnvhl           100             //100us
#define Tnvs            5               //5us
#define Tpgs            10              //10us
#define Trcv            1               //1us
#define Tpgh            20              //20ns          <----------------ns
#define Tprog           20              //20us


//Boot from 0x06000000, and switch 0c/0d/0e armba space, but disable jtag.
#define MC_BOOT_FROM_EFLASH     0x55555576
//Boot from 0x06000000, and switch 0c/0d/0e armba space, and enable jtag.
#define MC_BOOT_FROM_EFLASH_DBG 0x55555577

////////////////////////////////////////////////////////////////////////////////
//eflash configuration
#define EFLASH_INFO_BLOCK_START 0x06080000
#define EFLASH_INFO_BLOCK_SIZE  2048

#define EFLASH_BLOCK_SIZE       0x0800
#define EFLASH_REVISE           0

/* AHBEF32KX32C ʱ������Ĵ��� 1 ���� */
// [30-24] ���ȴ�״̬
#define EFLASH_TIMER1_RWS       0 //(0x19<<24)

// [23-16] ����Terase��Tme
#define EFLASH_TIMER1_MEH       ((250-1)<<16)

// [15-0] ����Terase��Tme
#define EFLASH_TIMER1_MEL       ((Terase*Fsysclk*4)-1)

/* AHBEF32KX32C ʱ������Ĵ��� 2 ���� */
// [26-16] ����Tnvh
#define EFLASH_TIMER2_NVH       ((Tnvh*Fsysclk-1)<<16)

// [15-0] ����Tnvhl
#define EFLASH_TIMER2_NVHL      ((Tnvhl*Fsysclk)-1)

/* AHBEF32KX32C ʱ������Ĵ��� 3 ���� */
// [27-16] ����Tpgs
#define EFLASH_TIMER3_PGS       (((Tpgs*Fsysclk)-1)<<16)

// [10-0] ����Tnvs
#define EFLASH_TIMER3_NVS       ((Tnvs*Fsysclk)-1)


/* AHBEF32KX32C ʱ������Ĵ��� 4 ���� */
// [28-20] ����Trcv
#define EFLASH_TIMER4_RCV       (((Trcv*Fsysclk)-1)<<20)

// [19-16] ����Tpgh
#define EFLASH_TIMER4_PGH       (0)

// [12-0] ����Tprog
#define EFLASH_TIMER4_PROG      ((Tprog*Fsysclk)-1)



/* AHBEF32KX32C ���ƼĴ��� 1 ���� */

// [31] ����ģʽʹ�ܣ��ߵ�ƽ��Ч
#define EFLASH_CTRL1_TMEN       (1<<31) 

#define AHBEFM_CTRL1_ERPR_ENA   (1<<29) //Erase and program enable, active high


// [28-24] ����ģʽ�µ�ʱ�����(��Чֵ >= 1)
#define EFLASH_CTRL1_TMV        (1<<24) 

// [18] ������ɺ���ж�ʹ�ܣ��ߵ�ƽ��Ч
#define EFLASH_CTRL1_INTEN      (1<<18) 

// [17] �������ʹ�ܣ��ߵ�ƽ��Ч
#define EFLASH_CTRL1_DBGOE      (1<<17) 

// [16] �Զ���������ʹ�ܣ��ߵ�ƽ��Ч
#define EFLASH_CTRL1_SERAUTO    (1<<16) 

// ����
#define EFLASH_CTRL1_RESET      0


/* AHBEF32KX32C ���ƼĴ��� 2 ���� */

// [8] �á�1����ʹ FLASH ���� TMMODE ָ���Ĳ���ģʽ.
#define EFLASH_CTRL2_TMENP      

// [4] �������ɺ��Զ��á�1����ͬʱ�� CPU �����ж������źš�д��0��������жϡ�
#define EFLASH_CTRL2_BERINT     (1<<4)

// [3] ����������ɺ��Զ��á�1����ͬʱ�� CPU �����ж������źš�д��0��������жϡ�
#define EFLASH_CTRL2_SERINT     (1<<3)

// [2] ����������ɺ��á�1����ER_EN �á�01�� �� ��10�����Զ����㡣 
#define EFLASH_CTRL2_EROVR      (1<<2)

// [1-0] 01���������� , 10��������� ����ֵ������������������ɺ��Զ����㡣
#define EFLASH_CTRL2_EREN_SECTOR    1
#define EFLASH_CTRL2_EREN_BULK      2

// ����
#define EFLASH_CTRL2_RESET          0


void eflash_init(void);

#endif // _EFLASH_H


