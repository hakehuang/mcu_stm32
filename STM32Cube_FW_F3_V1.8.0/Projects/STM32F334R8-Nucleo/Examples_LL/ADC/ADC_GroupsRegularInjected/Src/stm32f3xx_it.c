/** 
  ******************************************************************************
  * @file    Examples_LL/ADC/ADC_GroupsRegularInjected/Src/stm32f3xx_it.c
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    16-December-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_it.h"

/** @addtogroup STM32F3xx_LL_Examples
  * @{
  */

/** @addtogroup ADC_GroupsRegularInjected
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F3xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f3xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles external line 15_10 interrupt request.
  * @param  None
  * @retval None
  */
void USER_BUTTON_IRQHANDLER(void)
{
  /* Manage Flags */
  if(LL_EXTI_IsActiveFlag_0_31(USER_BUTTON_EXTI_LINE) != RESET)
  {
    /* Call interruption treatment function */
    UserButton_Callback();
    
    /* Clear EXTI line flag */
    /* Note: Clear flag after callback function to minimize user button       */
    /*       switch debounce parasitics.                                      */
    LL_EXTI_ClearFlag_0_31(USER_BUTTON_EXTI_LINE);
  }
}

/**
  * @brief  This function handles ADC2 interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
  /* Check whether ADC group injected end of unitary conversion caused        */
  /* the ADC interruption.                                                    */
  if(LL_ADC_IsActiveFlag_JEOC(ADC2) != 0)
  {
    /* Clear flag ADC group injected end of unitary conversion */
    LL_ADC_ClearFlag_JEOC(ADC2);
    
    /* Call interruption treatment function */
    AdcGrpInjectedUnitaryConvComplete_Callback();
  }
  
  /* Check whether ADC group regular overrun caused the ADC interruption */
  if(LL_ADC_IsActiveFlag_OVR(ADC2) != 0)
  {
    /* Clear flag ADC group regular overrun */
    LL_ADC_ClearFlag_OVR(ADC2);
    
    /* Call interruption treatment function */
    AdcGrpRegularOverrunError_Callback();
  }
}

/**
  * @brief  This function handles DMA1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel2_IRQHandler(void)
{
  /* Check whether DMA transfer complete caused the DMA interruption */
  if(LL_DMA_IsActiveFlag_TC2(DMA1) == 1)
  {
    /* Clear flag DMA transfer complete */
    LL_DMA_ClearFlag_TC2(DMA1);
    
    /* Call interruption treatment function */
    AdcDmaTransferComplete_Callback();
  }
  
  /* Check whether DMA half transfer caused the DMA interruption */
  if(LL_DMA_IsActiveFlag_HT2(DMA1) == 1)
  {
    /* Clear flag DMA half transfer */
    LL_DMA_ClearFlag_HT2(DMA1);
    
    /* Call interruption treatment function */
    AdcDmaTransferHalf_Callback();
  }
  
  /* Check whether DMA transfer error caused the DMA interruption */
  if(LL_DMA_IsActiveFlag_TE2(DMA1) == 1)
  {
    /* Clear flag DMA transfer error */
    LL_DMA_ClearFlag_TE2(DMA1);
    
    /* Call interruption treatment function */
    AdcDmaTransferError_Callback();
  }
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
