#ifndef __INIT_H
#define __INIT_H

void port_init(void);
void clk_init();
void tim1_init(uint16_t Prescaler, uint16_t Period);
void tim4_init(void);
void delay_us(uint16_t nCount);
void delay_ms(uint16_t nCount);

#endif /*__INIT_H*/
