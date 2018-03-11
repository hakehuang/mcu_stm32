
#include <math.h>
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
  
// HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
  HAL_GPIO_WritePin(GPIO0_PORT, GPIO0_PIN, GPIO_PIN_RESET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(GPIO0_PORT, GPIO0_PIN, GPIO_PIN_SET);
//  HAL_Delay(5000);
//  HAL_GPIO_WritePin(GPIO0_PORT, GPIO0_PIN, GPIO_PIN_RESET);
//  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
//  HAL_Delay(5000);
//  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
//  HAL_Delay(5000);
//  HAL_GPIO_TogglePin(GPIO0_PORT, GPIO0_PIN);
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
  int timeout_count = 100;
  int sample_count = 20;
  uint32_t freq_sum = 0;
  irq_tim = 0;
  
  while (sample_count){
     /*##-3- Start the Input Capture in interrupt mode ##########################*/
    if(HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL) != HAL_OK)
    {
      /* Starting Error */
      Error_Handler();
    }
    HAL_Delay(100);
    while(irq_tim == 0 && timeout_count)
    {
      HAL_Delay(100);
      timeout_count--;
    }
    
    if (0 == timeout_count)
    {
      printf("fail, timeout to get FREQ!\r\n");
      HAL_TIM_IC_Stop_IT(&TimHandle, TIM_CHANNEL);
      return;
    }
    else
    {
      /* skip first 5 samples since it's not accurate, use last 15 samples average */
      if (sample_count <= 15)
      {
        freq_sum += uwFrequency;
      }
      
      if (1 == sample_count)
      {
        printf("FREQ:%d \r\n", freq_sum/15);
        printf("RATIO:%d\r\n", 50);
      }
    }
    HAL_TIM_IC_Stop_IT(&TimHandle, TIM_CHANNEL);
    sample_count--;
  }
}

void adc_measure(void * param)
{
  __IO uint16_t uhADCxConvertedValue = 0;
  
  /* compute the value of voltage 500/1024 * 3.3(v) = 1611(mv)*/
  uint16_t expect_value = 1611;
  uint16_t actual_value = 0;
  
  if (HAL_ADC_Start(&AdcHandle) != HAL_OK)
  {
    /* Start Conversation Error */
    Error_Handler();
  }
  
  if (HAL_ADC_PollForConversion(&AdcHandle, 10) != HAL_OK)
  {
    /* End Of Conversion flag not set on time */
    Error_Handler();
  }
  else
  {
    /* ADC conversion completed */
    /*##-5- Get the converted value of regular channel  ########################*/
    uhADCxConvertedValue = HAL_ADC_GetValue(&AdcHandle);
    if (_strstr((char const *)param, "READ")!= NULL)
    {
      printf("DAC Output is %d", uhADCxConvertedValue);
    } else {
      actual_value = (uint16_t)((float)3300*uhADCxConvertedValue/4096);
      
      printf("DAC Output expected value is 1611, Measure value is %d !\r\n", actual_value);
      if((fabs(actual_value-expect_value)) < (expect_value/10.0))
      {
        printf("VOLTAGE_VERIFY_PASS !\n");
      }
      else
      {
        printf("VOLTAGE_VERIFY_FAIL !\n");
      }
    }
  }
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
  } else if (_strstr((char const *)param, "LOW")!= NULL) {
    HAL_GPIO_WritePin(GPIO2_PORT, GPIO2_PIN, GPIO_PIN_RESET);
  } else
  {
    HAL_GPIO_WritePin(GPIO2_PORT, GPIO2_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIO2_PORT, GPIO2_PIN, GPIO_PIN_SET);
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
    printf("LOW_LED_ON   PIN LOW\r\n");
  } else {
    printf("HIGH_LED_OFF   PIN HIGH\r\n");
  }
}


