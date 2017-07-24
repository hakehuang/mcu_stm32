/* Includes ------------------------------------------------------------------*/
#include <string.h>

#include "main.h"
#include "stm32f0xx_hal.h"
#include "board.h"
#include "function.h"



/* Private function prototypes -----------------------------------------------*/
#define MAXIMUM_TIMEOUT_MS 5000

void SystemClock_Config(void);

typedef void (*callback)(void * params);



typedef struct cmd_lut_t{
  char cmd[48];
  callback cb;
} CMD_LUT_T;


CMD_LUT_T cmd_luts [] = {
  {"RESET_BOARD", reset_board},
  {"sreset", sreset},
  {"FTM_0_ACT 0 EX_FTM_CAPTURE", tim_capture},
};


static int in_cmd = 0;

void HAL_SYSTICK_Callback(void)
{
  static int cnt = 0;
  if (in_cmd)
  {
    cnt++;
  }else {
    cnt = 0;
  }
  
  if (cnt > MAXIMUM_TIMEOUT_MS)
  {
    in_cmd = 0;
    NVIC_SystemReset();
  }
}

int main(void)
{
  volatile uint8_t recv_buf[100];
  
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();


  /* USER CODE BEGIN 2 */
  BSP_LED_Init();
  BSP_UART_Init();
  BSP_GPIO_Init();
  BSP_TIM_Init();


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  printf("\r\nHABS starts!!!\r\n");
   printf("\r %s \r\n", __DATE__);
  /*flash led once*/
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN);
  memset((void *)recv_buf, 0, sizeof(recv_buf));
  while (1)
  {
    volatile char ch = 0;
    irq_uart = 0;
    HAL_UART_Receive_IT(&huart1, (uint8_t*)&recv_buf, sizeof(recv_buf));
    
    while(irq_uart == 0)
    {
      //HAL_UART_Receive_IT(&huart1, (uint8_t*)&recv_buf, sizeof(recv_buf));
      HAL_Delay(100);
    }

    if(strstr((char *)recv_buf, "\r") == NULL )
    {
       printf("\r%s", recv_buf);
       if (huart1.RxXferCount == 0)
       {
          HAL_UART_Abort(&huart1);
          memset((void *)recv_buf, 0, sizeof(recv_buf));
       }
    } else {
      int i, meet = 0;
      HAL_UART_Abort(&huart1);
      for (i=0; i < sizeof(cmd_luts) / sizeof(CMD_LUT_T); i++)
      {
        if (strncmp((char const *)recv_buf, cmd_luts[i].cmd, strlen(cmd_luts[i].cmd))==0)
        {
          if (cmd_luts[i].cb)
          {
            printf("\r\nrunning %s\r\n", cmd_luts[i].cmd);
            in_cmd  = 1;
            cmd_luts[i].cb((void *)recv_buf);
            in_cmd = 0;
            meet = 1;
            printf("\r\nfinish %s\r\n", cmd_luts[i].cmd);
            break;
          }
        }
      }
      if (meet == 0)
      {
         printf("\rnot support %s\r\n", recv_buf);
      }
      memset((void *)recv_buf, 0, sizeof(recv_buf));
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