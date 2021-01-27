/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include <stdint.h>
#include <string.h>

#include "main.h"

volatile uint32_t time_ms_cnt=0;


/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
int main()
{
    pin_init();
    clk_init();
    tim4_init(125);
    tim1_init(16000,500);
    uart1_init(0,0);
    dog_init();
    feed_dog();
    uart1_put("\r\nstart stm8s\r\n");
    while(1)
    {
        if(time_ms_cnt%5000==0)
        {
            uart1_put("\r\nIt is running on STM8S baud 115200.");
            // uart1_set(time_ms_cnt/100);
            // printf("Test,%d\n",time_ms_cnt);
            delay_ms(300);
        }
    }
}

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
#ifdef __TIMER1_H
void tim1_isr(void) __interrupt(11)
{
    // time_ms_cnt++;
    TIM1->SR1 &= ~TIM1_SR1_UIF;
    // TIM1->SR1=0x00;
    GPIOB->ODR^=0x20;
    feed_dog();
}
#endif /*__TIMER1_H*/

#ifdef __TIMER4_H
void tim4_isr(void) __interrupt(23)
{
    time_ms_cnt++;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    // TIM4->SR1=0x00;
}
#endif /*__TIMER4_H*/

#ifdef __UART1_H
void uart1_isr(void) __interrupt(18)
{
    // Clear interrupt flag
    UART1->SR = 0xDF;
}
#endif /*__UART1_H*/

#ifdef __PIN_H
void pin_isr(void) __interrupt(6)
{
    // Clear interrupt flag
    // UART1->SR = 0xDF;
}
#endif /*__PIN_H*/

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
