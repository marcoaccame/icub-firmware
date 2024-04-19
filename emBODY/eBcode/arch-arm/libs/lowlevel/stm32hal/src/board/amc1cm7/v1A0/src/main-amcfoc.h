/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CAN2_TX_Pin GPIO_PIN_6
#define CAN2_TX_GPIO_Port GPIOB
#define CAN1_TX_Pin GPIO_PIN_1
#define CAN1_TX_GPIO_Port GPIOD
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define TRACED1_Pin GPIO_PIN_4
#define TRACED1_GPIO_Port GPIOE
#define TRACED0_Pin GPIO_PIN_3
#define TRACED0_GPIO_Port GPIOE
#define nLED1_Pin GPIO_PIN_5
#define nLED1_GPIO_Port GPIOD
#define TRACED2_Pin GPIO_PIN_2
#define TRACED2_GPIO_Port GPIOD
#define TRACED3_Pin GPIO_PIN_12
#define TRACED3_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define MCO_Pin GPIO_PIN_8
#define MCO_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define EEPR_nWP_Pin GPIO_PIN_13
#define EEPR_nWP_GPIO_Port GPIOC
#define TRACECLK_Pin GPIO_PIN_2
#define TRACECLK_GPIO_Port GPIOE
#define nLED2_Pin GPIO_PIN_4
#define nLED2_GPIO_Port GPIOD
#define CAN1_RX_Pin GPIO_PIN_0
#define CAN1_RX_GPIO_Port GPIOD
#define ETH_MISO_Pin GPIO_PIN_11
#define ETH_MISO_GPIO_Port GPIOC
#define ETH_SCLK_Pin GPIO_PIN_10
#define ETH_SCLK_GPIO_Port GPIOC
#define CAN2_STBY_Pin GPIO_PIN_10
#define CAN2_STBY_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define RTC_XTAL2_Pin GPIO_PIN_15
#define RTC_XTAL2_GPIO_Port GPIOC
#define RTC_XTAL1_Pin GPIO_PIN_14
#define RTC_XTAL1_GPIO_Port GPIOC
#define ETH_nRST_Pin GPIO_PIN_15
#define ETH_nRST_GPIO_Port GPIOG
#define ETH_MOSI_Pin GPIO_PIN_6
#define ETH_MOSI_GPIO_Port GPIOD
#define CAN1_STBY_Pin GPIO_PIN_9
#define CAN1_STBY_GPIO_Port GPIOA
#define ETH_nIRQ_Pin GPIO_PIN_6
#define ETH_nIRQ_GPIO_Port GPIOG
#define ETH_nIRQ_EXTI_IRQn EXTI9_5_IRQn
#define ETH_nPME_Pin GPIO_PIN_7
#define ETH_nPME_GPIO_Port GPIOG
#define ETH_nPME_EXTI_IRQn EXTI9_5_IRQn
#define IMU_INT2_Pin GPIO_PIN_4
#define IMU_INT2_GPIO_Port GPIOG
#define IMU_INT2_EXTI_IRQn EXTI4_IRQn
#define VER1_Pin GPIO_PIN_14
#define VER1_GPIO_Port GPIOD
#define VER0_Pin GPIO_PIN_13
#define VER0_GPIO_Port GPIOD
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
#define VER2_Pin GPIO_PIN_15
#define VER2_GPIO_Port GPIOD
#define nLED6_Pin GPIO_PIN_11
#define nLED6_GPIO_Port GPIOD
#define nLED4_Pin GPIO_PIN_9
#define nLED4_GPIO_Port GPIOD
#define nLED5_Pin GPIO_PIN_10
#define nLED5_GPIO_Port GPIOD
#define nLED3_Pin GPIO_PIN_8
#define nLED3_GPIO_Port GPIOD
#define CAN2_RX_Pin GPIO_PIN_12
#define CAN2_RX_GPIO_Port GPIOB
#define CAN_SHDN_Pin GPIO_PIN_3
#define CAN_SHDN_GPIO_Port GPIOA
#define IMU_INT1_Pin GPIO_PIN_1
#define IMU_INT1_GPIO_Port GPIOG
#define IMU_INT1_EXTI_IRQn EXTI1_IRQn
#define IMU_SDA_Pin GPIO_PIN_15
#define IMU_SDA_GPIO_Port GPIOF
#define PWR_nFAIL_Pin GPIO_PIN_0
#define PWR_nFAIL_GPIO_Port GPIOA
#define PWR_nFAIL_EXTI_IRQn EXTI0_IRQn
#define ETH_nSEL_Pin GPIO_PIN_4
#define ETH_nSEL_GPIO_Port GPIOA
#define EEPR_nSEL_Pin GPIO_PIN_0
#define EEPR_nSEL_GPIO_Port GPIOG
#define IMU_SCL_Pin GPIO_PIN_14
#define IMU_SCL_GPIO_Port GPIOF

/* USER CODE BEGIN Private defines */
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
