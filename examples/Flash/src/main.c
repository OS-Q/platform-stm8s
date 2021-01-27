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
__at(ID_ADDR) const uint8_t id = 42;
__at(USER_DATA_ADDR) uint8_t data[8];



void main()
{
    clk_init();
    uart1_init(0,0);
    // printf("\nID = %d. Data[0] = %d\n", id, data[0]);
    flash_unlock();
    for (int i = 0; i < sizeof(data); i++)
    {
        data[i] += id + i;
    }
    flash_lock();
    // printf("Data[0] = %d\n", data[0]);
    while (1)
    {
        LED1_TOG;
        delay_ms(300);
    }
}


/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
