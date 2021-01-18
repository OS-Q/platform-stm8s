#include <stdint.h>
#include <stm8s.h>
#include <delay.h>

#define OUTPUT_PIN      5

void timer_isr() __interrupt(TIM4_ISR)
{
    PB_ODR ^= (1 << OUTPUT_PIN);
    TIM4_SR &= ~(1 << TIM4_SR_UIF);
}
/* Clock output selection CCOSEL[3:0] */
#define F_CPU_CCO 0b0100
#define F_LSI_CCO 0b0001
#define F_HSI_CCO 0b1011
#define F_HSE_CCO 0b0010

void init(void)
{
    /* Enable HSE crystal oscillator */
    CLK_ECKR |= (1 << CLK_ECKR_HSEEN);
    while (!(CLK_ECKR & (1 << CLK_ECKR_HSERDY)));

    /* Switch master clock to HSE */
    CLK_SWR = 0xB4;
    while (!(CLK_SWCR & (1 << CLK_SWCR_SWIF)));
    CLK_SWCR |= (1 << CLK_SWCR_SWEN);

    /* Clock output on PC4 */
    PC_DDR |= (1 << 4);
    PC_CR1 |= (1 << 4);
    PC_CR2 |= (1 << 4);
    CLK_CCOR |= (1 << CLK_CCOR_CCOEN) | (F_CPU_CCO << 1);
}

void main()
{
    init();
    enable_interrupts();

    /* Set PB5 as output */
    PB_DDR |= (1 << OUTPUT_PIN);
    PB_CR1 |= (1 << OUTPUT_PIN);

    /* Prescaler = 128 */
    TIM4_PSCR = 0b00000111;

    /* Frequency = F_CLK / (2 * prescaler * (1 + ARR))
     *           = 2 MHz / (2 * 128 * (1 + 77)) = 100 Hz */
    // TIM4_ARR = 77;

    // TIM4_IER |= (1 << TIM4_IER_UIE); // Enable Update Interrupt
    // TIM4_CR1 |= (1 << TIM4_CR1_CEN); // Enable TIM4

    while (1)
    {
        // do nothing
        PB_ODR ^= (1 << OUTPUT_PIN);
        delay_ms(500);
    }
}
