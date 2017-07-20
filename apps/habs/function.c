
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


