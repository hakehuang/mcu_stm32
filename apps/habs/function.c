
#include "function.h"


void reset_board()
{
  //toogle led before do anything
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN);
  
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  return;
}


