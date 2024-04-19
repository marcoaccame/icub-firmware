/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    eth.h
  * @brief   This file contains all the function prototypes for
  *          the eth.c file
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
#ifndef __ETH_H__
#define __ETH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ETH_HandleTypeDef heth;

/* USER CODE BEGIN Private defines */
extern void HAL_ETH_GetTxConfig(ETH_HandleTypeDef* ethHandle, ETH_TxPacketConfig *pConfig);
extern void HAL_ETH_SetTxConfig(ETH_HandleTypeDef* ethHandle, const ETH_TxPacketConfig *pConfig);
/* USER CODE END Private defines */

void MX_ETH_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ETH_H__ */

