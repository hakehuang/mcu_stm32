#pragma once
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include <stdio.h>


void BSP_LED_Init();

void BSP_UART_Init();

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */