
#include "function.h"

void _memset(void * in, int val, size_t size)
{
  char * p = (char *)in;
  int count = 0;
  while(count < size)
  {
    count++;
    *p = val;
    p++;
  }
}

int _strlen(const char * in)
{
  char * p = (char *)in;
  int count = 0;
  while(*p != '\r' && *p != '\0' && *p != '\n')
  {
    p++;
    count++;
  }
  return count;
}

char * _strstr(const char * in, const char * cm)
{
  char *p = (char *)in;
  int len = _strlen(in);
  int count = 0;
  if (in == NULL || cm == NULL)
  {
    return NULL;
  }
  while(*p != '\r' && count < len && *p != '\0' && *p != '\n')
  {
    if(_strncmp(p, cm, _strlen(cm))==0)
    {
      return p;
    }
    count++;
    p++;
  }
  return NULL;
}


int _strncmp(const char * in, const char * cm, size_t len)
{
  char * pi = (char *)in;
  char * pc = (char *)cm;
  int count = 0;
  while(count < len)
  {
    if (*pi != *pc)
    {
      return 1;
    }
    pi++;
    pc++;
    count++;
  }
  return 0;
}

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

void tim_capture(void * param)
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

void gpio_2_operation(void * param)
{
    //toogle led before do anything
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  
  if (_strstr((char const *)param, "HIGH")!= NULL)
  {
   // HAL_GPIO_TogglePin(GPIO2_PORT, GPIO2_PIN);
    HAL_GPIO_WritePin(GPIO2_PORT, GPIO2_PIN, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIO2_PORT, GPIO2_PIN, GPIO_PIN_RESET);
  }
}

void gpio_1_operation(void * param)
{
  GPIO_PinState ret = GPIO_PIN_RESET;
    //toogle led before do anything
  HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_PIN); 
  HAL_Delay(100);
  
  ret = HAL_GPIO_ReadPin(GPIO1_PORT, GPIO1_PIN);
  if (ret == GPIO_PIN_RESET)
  {
    printf("PIN LOW\r\n");
  } else {
    printf("PIN HIGH\r\n");
  }
}


