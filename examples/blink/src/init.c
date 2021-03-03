/*******************************************************************************
****版本：V1.0.0
****平台：STM8S003
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/

#include "stm8s.h"
#include "init.h"

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void port_init()
{
    PA_ODR = 0x00;
    PA_DDR = 0xFF;
    PA_CR1 = 0xFF;
    PA_CR2 = 0x00;

    PB_ODR = 0x00;
    PB_DDR = 0xFF;
    // PIN B 45 I2C is open drain
    PB_CR1 = 0xCF;
    PB_CR2 = 0x00;

    PC_ODR = 0x00;
    PC_DDR = 0xFF;
    PC_CR1 = 0xFF;
    PC_CR2 = 0x00;

    PD_ODR = 0x00;
    PD_DDR = 0xFF;
    PD_CR1 = 0xFF;
    PD_CR2 = 0x00;
}

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/

void clk_init()
{
    nointerrupts();
    CLK_ICKR = 0;
    CLK_ICKR |= CLK_ICKR_HSIEN; //开启内部HSI
    CLK_ECKR = 0;
    CLK_SWR = CLK_SWR_HSI;      //HSI为主时钟源
    CLK_CKDIVR=0x00;            //HSI不分频
    while (0 == (CLK_ICKR & CLK_ICKR_HSIRDY)); //HSI准备就绪
    // CLK_CKDIVR = 0;
    // CLK_CKDIVR = (uint8_t)(~0x18);/*使能内部时钟*/
    CLK_PCKENR1 = 0xFF;
    CLK_PCKENR2 = 0xFF;
    CLK_CCOR = 0;
    CLK_HSITRIMR = 0;
    CLK_SWIMCCR = 0;

    CLK_SWCR = 0;
    CLK_SWCR |= CLK_SWCR_SWEN;
    while (0 != (CLK_SWCR & CLK_SWCR_SWBSY));
    interrupts();
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void delay_ms(unsigned int ms)
{
    unsigned char i;
    while(ms!=0)
    {
        for(i=0;i<120;i++){}
        for(i=0;i<120;i++){}
        ms--;
    }
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
