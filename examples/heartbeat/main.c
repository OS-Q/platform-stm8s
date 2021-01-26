#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_clk.h"
#include "stm8s_tim4.h"

#define LED_PORT GPIOA
#define LED GPIO_PIN_1

#define TIM4_PERIOD             124
#define TIM4_US_PERIOD          4

volatile uint16_t count;

INTERRUPT_HANDLER(IRQ_Handler_TIM4, 23) {
    if (count) {
        count--;
    }

    TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}

void delay_ms(uint16_t ms) {
    TIM4_Cmd(DISABLE);
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

    count = ms;

    TIM4_Cmd(ENABLE);

    while(count);
}

int main( void ) {
    /* This delay should be added just after reset to have access to SWIM pin
    and to be able to reprogram the device after power on (otherwise the device
    will be locked) */
    __asm
    pushw x
    push a
    ldw x, #0xFFFF
    loop1: ld a, #50
    loop2: dec a
    jrne loop2
    decw x
    jrne loop1
    pop a
    popw x
    __endasm;

    // Set 16 MHz for CPU
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(LED_PORT, LED, GPIO_MODE_OUT_PP_LOW_FAST);
    enableInterrupts();

    unsigned int sequence[] = {200, 100, 200, 500};

    uint8_t sequence_index = 0;
    uint8_t sequence_length = 4;
    while (1) {
        delay_ms(sequence[sequence_index]);
        sequence_index++;
        if (sequence_index == sequence_length) {
            sequence_index = 0;
        }
        GPIO_WriteReverse(LED_PORT, LED);
    }
}

// This is called by some of the SPL files on error.
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;

      /* User can add their own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

      /* Infinite loop */
      while (1){
      }
}
#endif
