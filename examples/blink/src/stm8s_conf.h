
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

#include "stm8s_clk.h"
// #include "stm8s_spi.h"
// #include "stm8s_uart1.h"


#define USE_FULL_ASSERT    (0)
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif

#endif /* __STM8S_CONF_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
