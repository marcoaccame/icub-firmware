
/*
 * Copyright (C) 2024 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_bsp.h"


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include <cstring>
#include <vector>
#include <array>

#include "embot_core_binary.h"
#include "embot_core.h"

#if defined(USE_STM32HAL)
    #include "stm32hal.h"
#else
    #warning this implementation is only for stm32hal
#endif


using namespace std;
using namespace embot::core::binary;

// --------------------------------------------------------------------------------------------------------------------
// - configuration of peripherals and chips. it is done board by board. it contains a check vs correct STM32HAL_BOARD_*
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_bsp_config.h"


// --------------------------------------------------------------------------------------------------------------------
// - support maps
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - specialize the bsp
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_bsp_amcfoc_1cm7.h"


namespace embot::hw::bsp::amcfoc1cm7 {
        


}


#if     !defined(EMBOT_ENABLE_hw_bsp_specialize)
bool embot::hw::bsp::specialize() { return true; }
#else   

    bool embot::hw::bsp::specialize()
    {
        // all the rest
        // nothing for now
//        __HAL_RCC_GPIOB_CLK_ENABLE();
//        __HAL_RCC_GPIOG_CLK_ENABLE();
//        __HAL_RCC_GPIOD_CLK_ENABLE();
//        __HAL_RCC_GPIOC_CLK_ENABLE();
//        __HAL_RCC_GPIOH_CLK_ENABLE();
//        __HAL_RCC_GPIOA_CLK_ENABLE();
//        __HAL_RCC_GPIOF_CLK_ENABLE();
//        __HAL_RCC_GPIOE_CLK_ENABLE();        
        
        return true;
    }

#endif  //EMBOT_ENABLE_hw_bsp_specialize




// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

