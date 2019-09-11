/*
 * Copyright (C) 2017 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _EMBOT_APP_APPLICATION_THECANPARSERPOS_H_
#define _EMBOT_APP_APPLICATION_THECANPARSERPOS_H_

#include "embot_common.h"
#include "embot_hw_can.h"
#include "embot_sys.h"
#include <vector>
#include <memory>

#include "embot_app_canprotocol.h"
#include "embot_app_canprotocol_analog_polling.h"
#include "embot_app_canprotocol_analog_periodic.h"

namespace embot { namespace app { namespace application {
    
    class CANagentPOS
    {
    public:
        
        // interface    
        virtual bool set(const embot::app::canprotocol::analog::polling::Message_POS_CONFIG_SET::Info &info) = 0;
        virtual bool set(const embot::app::canprotocol::analog::polling::Message_POS_TRANSMIT::Info &info) = 0;
    
        virtual bool get(const embot::app::canprotocol::analog::polling::Message_POS_CONFIG_GET::Info &info, embot::app::canprotocol::analog::polling::Message_POS_CONFIG_GET::ReplyInfo &replyinfo) = 0;
       
    public:
        virtual ~CANagentPOS() {};         
    };
    
           
    class theCANparserPOS
    {
    public:
        static theCANparserPOS& getInstance();
        
    public:
        
        struct Config
        {
            CANagentPOS* agent {nullptr};
            Config() = default;
            Config(CANagentPOS* a) : agent(a) {}
            bool isvalid() { return (nullptr == agent) ? false : true; }
        }; 
        
        
        bool initialise(Config &config); 
        
        // returns true if the canframe has been recognised. if so, any reply is sent if replies.size() > 0
        bool process(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);

    private:
        theCANparserPOS(); 
        ~theCANparserPOS();


    private:    
        struct Impl;
        std::unique_ptr<Impl> pImpl;        
    };       


}}} // namespace embot { namespace app { namespace application


#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------