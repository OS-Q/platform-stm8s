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

void opt_write()
{
    /* new value for OPT5 (default is 0x00) */
    uint8_t opt5 = 0xb2;

    if (OPT5 != opt5)
    {
        /* unlock EEPROM and option bytes */
        eeprom_unlock();
        option_bytes_unlock();

        /* write option byte and it's complement */
        OPT5 = opt5;
        NOPT5 = ~opt5;

        /* wait until programming is finished and lock EEPROM */
        eeprom_wait_busy();
        eeprom_lock();
    }
}

void main(void)
{
    // uint8_t opt5 = OPT5;
    clk_init();
    uart1_init(0,0);
    uart1_put("\nWriting option bytes..\n");
    opt_write();
    // printf("OPT5 changed from %02x to %02x\n", opt5, OPT5);
    while (1)
    {

    }
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
