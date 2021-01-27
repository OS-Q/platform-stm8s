/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "main.h"

/* Use last 64 bytes of flash for user data */
#define ID_ADDR                 (0x8000 + 0x1FC0)
#define USER_DATA_ADDR          (ID_ADDR + 1)

/* Tell compiler where the variables are located.
 * Defining variable as const will place it in the firmware binary */
__at(ID_ADDR) const uint8_t id = 0x30;
__at(USER_DATA_ADDR) uint8_t data[16];

void led_init(void)
{
    GPIOB->DDR|=0x20;
    GPIOB->CR1|=0x20;
    GPIOB->CR2|=0x00;
}


void main()
{
    char str[] = "Test Flash string\n";
    int len = sizeof (str);
    clk_init();
    pin_init();
    uart1_init(0,0);
    flash_unlock();
    for (int i = 0; i < len; i++)
    {
        data[i] = str[i];
        str[i] = 0 ;
    }
    flash_lock();
    for (int i = 0; i < len; i++)
    {
        str[i] = data[i];
    }
    uart1_put(str);
    while (1)
    {
        LED1_TOG;
        delay_ms(300);
    }
}


/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
