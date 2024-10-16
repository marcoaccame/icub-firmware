/*******************************************************************************************************************//**
 * @file    adcm.h
 * @author  G.Zini
 * @version 1.0
 * @date    2021 September, 27
 * @brief   A/D converter management for CM4 core
 **********************************************************************************************************************/

/* Define to prevent recursive inclusion */
#ifndef __ADCM_H
#define __ADCM_H

#ifdef __cplusplus
    extern "C" {
#endif


/* Includes ----------------------------------------------------------------------------------------------------------*/
        
#if defined(USE_STM32HAL)
#include "stm32hal.h"     
#define MOTORHAL_changes
#else
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>        
#include "main.h"
#include "stm32h7xx.h"
#endif        


/* Exported typedefs -------------------------------------------------------------------------------------------------*/

typedef enum
{
    ADCMOT_PHASE_U,
    ADCMOT_PHASE_V,
    ADCMOT_PHASE_W
} AdcMotPhase_t;


/* Exported functions prototypes -------------------------------------------------------------------------------------*/

extern HAL_StatusTypeDef AdcMotInit(void);
extern void AdcMotDeInit(void);
extern void AdcMotGetCurrents(int16_t *pU, int16_t *pV, int16_t *pW);
extern void AdcMotGetVoltages(uint16_t *pU, uint16_t *pV, uint16_t *pW);
extern uint32_t AdcMotGetOffset(AdcMotPhase_t Phase);
extern void AdcMotSetOffset(AdcMotPhase_t Phase, uint16_t Offset);



#if defined(MOTORHAL_changes)
// we need to expose the callbacks
extern void AdcMotHalfTransfer_cb(ADC_HandleTypeDef *hadc);
extern void AdcMotTransferComplete_cb(ADC_HandleTypeDef *hadc);

// we need to be bale to specify a user-defined function when the currents are available
typedef void (*adcm_fp_int16_int16_uint16_t) (int16_t, int16_t, int16_t);
extern adcm_fp_int16_int16_uint16_t adcm_FP_on_acquisition_of_currents;

#endif


#ifdef __cplusplus
    } /* extern "C" */
#endif /* __cplusplus */

#endif /* __ADCM_H */
/* END OF FILE ********************************************************************************************************/
