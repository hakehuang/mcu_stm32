
#include "function.h"




void reset_board(void * param)
{
  //toogle led before do anything
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN);
  
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_Delay(2000);
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  return;
}

void delay_to_reset(void * param)
{
    //toogle led before do anything
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN);
  while(1)
  {
    HAL_Delay(100);
  }
}

void sreset(void * param)
{
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);

  NVIC_SystemReset();
}

void tim_capture()
{
  irq_tim = 0;
   /*##-3- Start the Input Capture in interrupt mode ##########################*/
  if(HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  HAL_Delay(100);
  while(irq_tim == 0)
  {
    HAL_Delay(100);
  }
  printf("FREQ: %d \r\n", uwFrequency);
  printf("RATIO: %d\r\n", 50);
}


