/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Alessandro Scalzo
 * email:   alessandro.scalzo@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or  FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License foFITNESSr more details
*/


#ifndef MC_MOTOR_HID_H___
#define MC_MOTOR_HID_H___


#include "WatchDog.h"


typedef union
{
    struct
    {
        //B0 L
        unsigned ExternalFaultAsserted  :1;
        unsigned UnderVoltageFailure    :1;      
        unsigned OverVoltageFailure     :1;
        unsigned OverCurrentFailure     :1;
        //B0 H
        unsigned DHESInvalidValue       :1;
        unsigned AS5045CSumError        :1;
        unsigned DHESInvalidSequence    :1;
        unsigned CANInvalidProtocol     :1;
        //B1 L
        unsigned CAN_BufferOverRun      :1;
        unsigned SetpointExpired        :1;
        unsigned CAN_TXIsPasv           :1;
        unsigned CAN_RXIsPasv           :1;
        //B1 H
        unsigned CAN_IsWarnTX           :1;
        unsigned CAN_IsWarnRX           :1;
        unsigned unused                 :1;
        unsigned OverHeating            :1;
        //B2 L
        unsigned ADCCalFailure          :1; 
        unsigned I2TFailure             :1;                     
        unsigned EMUROMFault            :1;
        unsigned EMUROMCRCFault         :1;
        //B2 H
        unsigned EncoderFault           :1;
        unsigned FirmwareSPITimingError :1;		
        unsigned AS5045CalcError        :1;
        unsigned FirmwarePWMFatalError  :1;
        //B3 L
        unsigned CAN_TXWasPasv          :1;
        unsigned CAN_RXWasPasv          :1;
        unsigned CAN_RTRFlagActive      :1;
        unsigned CAN_WasWarn            :1;
        //B3 H
        unsigned CAN_DLCError           :1;
        unsigned SiliconRevisionFault   :1;
        unsigned PositionLimitUpper     :1; 
        unsigned PositionLimitLower     :1; 
    } bits;
        
    uint32_t bitmask;
        
} MotorFaultState;

typedef union
{
    struct
    {
        unsigned dirty           :1;
        unsigned stuck           :1;
        unsigned index_broken    :1;
        unsigned phase_broken    :1;
        
        unsigned not_calibrated  :1;
        unsigned unused          :3;
    } bits;
    uint8_t bitmask;
} QEState;

typedef struct //State2FocMsg
{
    uint8_t control_mode;
    
    //QEState qe_state;
    uint8_t qe_state;
    
    int16_t pwm_fbk;
    
    //FaultState fault_state;
    uint32_t fault_state;
    
} State2FocMsg;

typedef struct //HardStopCalibData
{
    union
    {
        struct
        {
            unsigned iscalibrating   :1;
            unsigned hwlimitreached  :1;
            unsigned unused          :6;
        } bits;
        uint8_t bitmask;
    }u;
    uint8_t posStable_counter;
    uint16_t waitcalib_counter;
    int32_t limited_pwm;
    int32_t last_pos;
    int32_t zero;
    
} HardStopCalibData;

struct Motor_hid
{
    // the location of the hw actuator. it can hold: 
    // - a can location in case of actuators on the CAN bus (foc / amcbldc boards)
    // - an eth location in case of actuator(s) on the same board (mc4plus, second core, ...)
    eObrd_location_t mlocation;
    
    // it tells what type of hw actuation controls the motor: 
    // HARDWARE_MC4p (pwm ports of a mc4plus), 
    // HARDWARE_2FOC (boards foc, amcbldc, amc2c, ...)
    MC_MOTOR_HARDWARE_t HARDWARE_TYPE;
    
    
    // the number ID: 0, 1, 2 or 3
    uint8_t ID;
    

    CTRL_UNITS GEARBOX;

    uint32_t partial_timer;
    int32_t  partial_space;

    BOOL HAS_TEMP_SENSOR;
    int16_t temperature_max;
    int16_t temperature_fbk;

    int32_t pwm_max;
    int32_t pwm_fbk;
    int32_t pwm_ref;
    
    int32_t calib_pwm;
    
    int32_t pos_raw_cal_fbk;
    int32_t pos_raw_fbk;
    int32_t pos_raw_fbk_old;
    int32_t vel_raw_fbk;
    
    int32_t pos_calib_offset;
    
    int32_t pos_min;
    int32_t pos_max;
    int32_t pos_ref;
    int32_t pos_fbk;
    int32_t pos_err;
    
    int32_t pos_fbk_old;
    int32_t enc_sign;
    float32_t enc_tolerance;
    
    int32_t vel_max;
    int32_t vel_ref;
    int32_t vel_fbk;
    int32_t vel_err;
    
    int32_t Iqq_max;
    int32_t Iqq_ref;
    int32_t Iqq_fbk;
    int32_t Iqq_ovl;
    int32_t Iqq_err;
    
    CTRL_UNITS trq_max;
    CTRL_UNITS trq_ref;
    CTRL_UNITS trq_fbk;
    CTRL_UNITS trq_err;
    
    int32_t output;
    
    PID trqPID;
    
    BOOL not_init;
    BOOL not_calibrated;
    BOOL hardware_fault;
    
    BOOL can_dead;
    BOOL wrong_ctrl_mode;
    
    uint16_t diagnostics_refresh;
    uint16_t diagnostics_refresh_warning;
    MotorFaultState fault_state_prec;
    MotorFaultState fault_state;
    QEState qe_state;
    
    icubCanProto_controlmode_t  control_mode;
    icubCanProto_controlmode_t  control_mode_req;
    WatchDog control_mode_req_wdog;

    HardStopCalibData hardstop_calibdata;

    uint16_t qencoder_err_counter;

    // 2FOC specific data
    WatchDog can_2FOC_alive_wdog;
    uint8_t can_motor_config[7];
    //BOOL outOfLimitsSignaled;

};


 
#endif  // include-guard

