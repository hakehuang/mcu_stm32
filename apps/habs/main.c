/* Includes ------------------------------------------------------------------*/
#include <string.h>

#include "main.h"
#include "stm32f0xx_hal.h"
#include "board.h"
#include "function.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

typedef void (*callback)(void * params);



typedef struct cmd_lut_t{
  char cmd[48];
  callback cb;
} CMD_LUT_T;




CMD_LUT_T cmd_luts [] = {
  {"RESET_BOARD", reset_board},
};


int main(void)
{
  uint8_t recv_buf[100];
  int count = 0;
  
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();


  /* USER CODE BEGIN 2 */
  BSP_LED_Init();
  BSP_UART_Init();
  BSP_GPIO_Init();


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  printf("\r\nHABS starts!!!\r\n");
   printf("\r\n %s \r\n", __DATE__);
  /*flash led once*/
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN);
  memset(recv_buf, 0, sizeof(recv_buf));
  while (1)
  {
    char ch = 0;

    while( HAL_OK != HAL_UART_Receive(&huart1, (uint8_t*)&ch, 1, 500000))
    {
      ;
    }

    if(ch != 0x0d)
    {
       recv_buf[count%100] = ch;
       printf("%c", ch);
       count++;
    } else if (count > 0){
      int i;
      recv_buf[count%100] = '\0';
      
      for (i=0; i < sizeof(cmd_luts) / sizeof(CMD_LUT_T); i++)
      {
        if (strncmp((char const *)recv_buf, cmd_luts[i].cmd, count)==0)
        {
          if (cmd_luts[i].cb)
          {
            printf("\r\nrunning %s\r\n", cmd_luts[i].cmd);
            cmd_luts[i].cb(recv_buf);
          }
        }
      }
      memset(recv_buf, 0, sizeof(recv_buf));
      count = 0;
    }
  } 
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif