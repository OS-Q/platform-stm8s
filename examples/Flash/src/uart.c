#include "uart.h"
#include "stm8s.h"

void uart_init()
{
    /* round to nearest integer */

    PD_DDR = 0xBF;
    PD_CR1 = 0xFF;
    // uint16_t div = (F_CPU + BAUDRATE / 2) / BAUDRATE;
    // UART1_BRR2 = ((div >> 8) & 0xF0) + (div & 0x0F);
    // UART1_BRR1 = div >> 4;
    UART1_BRR2 = 0x0B;
    UART1_BRR1 = 0x08;
    /* Enable TX & RX */
    UART1_CR2 = (1 << 3) | (1 << 2);
    /* 1 stop bit */
    UART1_CR3 &= ~((1 << 5) | (1 << 4));
    /* enable transmitter and receiver */
    UART1_CR2 = (1 << UART1_CR2_TEN) | (1 << UART1_CR2_REN);
}

void uart_write(uint8_t data) {
    UART1_DR = data;
    while (!(UART1_SR & (1 << UART1_SR_TC)));
}

uint8_t uart_read() {
    while (!(UART1_SR & (1 << UART1_SR_RXNE)));
    return UART1_DR;
}
