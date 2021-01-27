/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/

#include "main.h"

void eeprom_read(uint16_t addr, uint8_t *buf, int len)
{
    while (len--) *(buf++) = _MEM_(addr++);
}


void main()
{
    char data[] = "Test EE string\n";
    int len = sizeof (data);
    uint16_t addr = EEPROM_START_ADDR;
    clk_init();
    pin_init();
    uart1_init(0,0);
    eeprom_unlock();
    for (int i = 0; i < len; i++, addr++)
    {
        _MEM_(addr) = data[i];
        data[i] = 0;
        /* not necessary on devices with no RWW support */
        // eeprom_wait_busy();
    }
    eeprom_lock();
    eeprom_read(EEPROM_START_ADDR, data, len);
    uart1_put(data);
    // for (int i = 0; i < len; i++)
    // {
    //     uart1_set(data[i]);
    // }
    while (1)
    {
        // printf("Reading EEPROM: %s\n", buf);
        LED1_TOG;
        delay_ms(250);
    }
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
