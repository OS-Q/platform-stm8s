
#include "stm8s.h"
#include "stm8s_it.h"    /* SDCC patch: required by SDCC for interrupts */


/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO TestStatus OperationStatus;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


void main(void)
{

    uint8_t val = 0x00, val_comp = 0x00;
    uint32_t add = 0x00;

    /* Define FLASH programming time */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

    /* Unlock Data memory */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);

    /* Read a byte at a specified address */
    add = 0x40A5;
    val = FLASH_ReadByte(add);

    /* Program complement value (of previous read byte) at previous address + 1 */
    val_comp = (uint8_t)(~val);
    FLASH_ProgramByte((add + 1), val_comp);

    /* Check program action */
    val = FLASH_ReadByte((add + 1));
    if (val != val_comp)
    {
        /* Error */
        OperationStatus = FAILED;
        /* OperationStatus = PASSED, if the data written/read to/from DATA EEPROM memory is correct */
        /* OperationStatus = FAILED, if the data written/read to/from DATA EEPROM memory is corrupted */
        while (1)
        {
        }
    }

    /* Erase byte at a specified address & address + 1 */
    FLASH_EraseByte(add);
    FLASH_EraseByte((add + 1));
    /* Erase action */
    val = FLASH_ReadByte(add);
    val_comp = FLASH_ReadByte((add + 1));
    if ((val != 0x00) & (val_comp != 0x00))
    {
        /* Error */
        OperationStatus = FAILED;
        /* OperationStatus = PASSED, if the data written/read to/from DATA EEPROM memory is correct */
        /* OperationStatus = FAILED, if the data written/read to/from DATA EEPROM memory is corrupted */
        while (1)
        {
        }
    }

    /* Pass */
    OperationStatus = PASSED;
    /* OperationStatus = PASSED, if the data written/read to/from DATA EEPROM memory is correct */
    /* OperationStatus = FAILED, if the data written/read to/from DATA EEPROM memory is corrupted */
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
