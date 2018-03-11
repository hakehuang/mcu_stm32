#pragma once
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include <stdio.h>


extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef TimHandle;
extern ADC_HandleTypeDef AdcHandle;
extern uint32_t uwFrequency;

void BSP_LED_Init();

void BSP_UART_Init();

void BSP_GPIO_Init();

void BSP_TIM_Init();

void BSP_ADC_Init();

int getkey(void);

extern volatile int irq_uart;
extern volatile int irq_tim;

#ifdef stm32f03_evk
#define UART_INST USART1
#define UART_PORT GPIOA
#define UART_PIN_TX GPIO_PIN_9
#define UART_PIN_RX GPIO_PIN_10
#define GPIO0_PIN GPIO_PIN_0
#define GPIO0_PORT GPIOA
#define GPIO_LED_PIN GPIO_PIN_4
#define GPIO1_PIN GPIO_PIN_1
#define GPIO1_PORT GPIOA
#define GPIO_LED_PORT GPIOA
#define GPIO2_PIN GPIO_PIN_2
#define GPIO2_PORT GPIOA
#define TIM_INSTANCE TIM14
#define TIM_CHANNEL TIM_CHANNEL_1
#define TIM_GPIO_PORT GPIOB
#define TIM_PIN  GPIO_PIN_1
#define TIM_PIN_AF GPIO_AF0_TIM14
#define TIM_IRQ_NUM TIM14_IRQn

/* Definition for ADCx clock resources */
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()

#define ADCx_FORCE_RESET()              __HAL_RCC_ADC1_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC1_RELEASE_RESET()
/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                GPIO_PIN_3
#define ADCx_CHANNEL_GPIO_PORT          GPIOA

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                    ADC_CHANNEL_3
#define SAMPLINGTIME                    ADC_SAMPLETIME_7CYCLES_5
#endif
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */