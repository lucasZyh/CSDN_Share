/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART1 global interrupt.
  */
//void USART1_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART1_IRQn 0 */

//  /* USER CODE END USART1_IRQn 0 */
//  HAL_UART_IRQHandler(&huart1);
//  /* USER CODE BEGIN USART1_IRQn 1 */

//  /* USER CODE END USART1_IRQn 1 */
//}

/**
  * @brief This function handles USART3 global interrupt.
  */
//void USART3_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART3_IRQn 0 */

//  /* USER CODE END USART3_IRQn 0 */
//  HAL_UART_IRQHandler(&huart3);
//  /* USER CODE BEGIN USART3_IRQn 1 */
//    uint8_t tmp;
//    
//    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE) != RESET)        /* UART���չ��ش����ж� */
//    {
//        __HAL_UART_CLEAR_OREFLAG(&huart3);                           /* ������չ��ش����жϱ�־ */
//        (void)huart3.Instance->SR;                                   /* �ȶ�SR�Ĵ������ٶ�DR�Ĵ��� */
//        (void)huart3.Instance->DR;
//    }
//    
//    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) != RESET)       /* UART�����ж� */
//    {
//        HAL_UART_Receive(&huart3, &tmp, 1, HAL_MAX_DELAY);           /* UART�������� */
//        if (g_uart_rx_frame.sta.len < (256 - 1))   /* �ж�UART���ջ����Ƿ����
//                                                                             * ����һλ��������'\0'
//                                                                             */
//        {
//            g_uart_rx_frame.buf[g_uart_rx_frame.sta.len] = tmp;             /* �����յ�������д�뻺�� */
//            g_uart_rx_frame.sta.len++;                                      /* ���½��յ������ݳ��� */
//        }
//        else                                                                /* UART���ջ������ */
//        {
//            g_uart_rx_frame.sta.len = 0;                                    /* ����֮ǰ�յ������� */
//            g_uart_rx_frame.buf[g_uart_rx_frame.sta.len] = tmp;             /* �����յ�������д�뻺�� */
//            g_uart_rx_frame.sta.len++;                                      /* ���½��յ������ݳ��� */
//        }
//    }
//    
//    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) != RESET)       /* UART���߿����ж� */
//    {
//        g_uart_rx_frame.sta.finsh = 1;                                      /* ���֡������� */
//        
//        __HAL_UART_CLEAR_IDLEFLAG(&huart3);                          /* ���UART���߿����ж� */
//    }
//  /* USER CODE END USART3_IRQn 1 */
//}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
