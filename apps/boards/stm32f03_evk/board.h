#pragma once
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include <stdio.h>


extern UART_HandleTypeDef huart1;

void BSP_LED_Init();

void BSP_UART_Init();

void BSP_GPIO_Init();

int getkey(void);

extern volatile int irq;

#ifdef stm32f03_evk
#define GPIO0_PIN GPIO_PIN_0
#define GPIO0_PORT GPIOA
#define GPIO_LED_PIN GPIO_PIN_4
#define GPIO_LED_PORT GPIOA
#endif
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */