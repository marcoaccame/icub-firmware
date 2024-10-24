
/*
 * Copyright (C) 2023 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/



// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_app_application_theCANagentCORE.h"


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "embot_core.h"
#include "embot_core_binary.h"

#include <new>

#include "embot_app_theCANboardInfo.h"
#include "embot_hw_sys.h"
#include "embot_hw_can.h"

// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------


struct embot::app::application::theCANagentCORE::Impl
{  
        
    Config _config {};
        
    embot::app::theCANboardInfo::StoredInfo _storedinfo = {0};  
    
    embot::prot::can::applicationInfo _applicationinfo {};


    embot::prot::can::Board _board {embot::prot::can::Board::unknown};
      
    Impl() { }
    
                
    bool initialise(const Config &config);
    
    bool setcanaddress(const std::uint8_t adr, const std::uint16_t randominvalidmask);
};

bool embot::app::application::theCANagentCORE::Impl::initialise(const Config &config)
{
    _config = config;
    
    // make sure to synch the application version and can protocol to the eeprom storage
    embot::app::theCANboardInfo::getInstance().synch(_config.applicationinfo.version, _config.applicationinfo.protocol);
            
    // retrieve board type, version of application, can address
    // we use the object theCANboardInfo which is based onto FlashStorage which manages 
    // the flash partition called Partition::ID::sharedstorage

    if(true == embot::app::theCANboardInfo::getInstance().get(_storedinfo))
    {
        _board = static_cast<embot::prot::can::Board>(_storedinfo.boardtype);
//        _address = _storedinfo.canaddress;
        _applicationinfo.version.major = _storedinfo.applicationVmajor;
        _applicationinfo.version.minor = _storedinfo.applicationVminor;
        _applicationinfo.version.build = _storedinfo.applicationVbuild;
        _applicationinfo.protocol.major = _storedinfo.protocolVmajor;
        _applicationinfo.protocol.minor = _storedinfo.protocolVminor;                
    }
    
    // note: we could make it even more general by using inside _config a pure interface class which
    // does the job of theCANboardInfo, in such a way we just specialise this class ... but maybe later
         
    return true;
}
 

bool embot::app::application::theCANagentCORE::Impl::setcanaddress(const std::uint8_t adr, const std::uint16_t randominvalidmask)
{
    embot::app::theCANboardInfo &canbrdinfo = embot::app::theCANboardInfo::getInstance();
    
    // i reinforce a reading from storage. just for safety. in here we are dealing w/ can address change and i want to be sure.
    std::uint8_t canaddress = canbrdinfo.getCANaddress();
    
    std::uint8_t target = adr;
    
    if(0xff == adr)
    {
        // compute a new random address. use the randoinvalid mask to filter out the undesired values. for sure 0x8001.
        std::uint16_t mask = randominvalidmask;
        mask |= 0x8001;
        if(0xffff == mask)
        {   // hei, nothing is good for you.
            return false;
        }
        
        bool ok = false;
        for(std::uint16_t i=0; i<250; i++)
        {
            target = (embot::hw::sys::random()-embot::hw::sys::minrandom()) & 0xf;
           
            if(false == embot::core::binary::bit::check(mask, target))
            {
                ok = true;
                break;                    
            }
        }
        
        if(!ok)
        {
            return false;
        }
    }
    
    // always check that is is not 0 or 0xf
    if((0 == target) || (0xf == target))
    {
        return false;
    }
        
    
    if(canaddress != target)
    {
        if(embot::hw::resOK != embot::hw::can::setfilters(_config.canbus, target))
        {
            return false;
        }
        canbrdinfo.setCANaddress(target);
        canaddress = canbrdinfo.getCANaddress();
    }
                    
    return (target == canaddress);
}


// --------------------------------------------------------------------------------------------------------------------
// - the class
// --------------------------------------------------------------------------------------------------------------------


embot::app::application::theCANagentCORE& embot::app::application::theCANagentCORE::getInstance()
{
    static theCANagentCORE* p = new theCANagentCORE();
    return *p;
}

embot::app::application::theCANagentCORE::theCANagentCORE()
{
    pImpl = std::make_unique<Impl>();
}  

    
embot::app::application::theCANagentCORE::~theCANagentCORE() { }
   
        
bool embot::app::application::theCANagentCORE::initialise(const Config &config)
{
    return pImpl->initialise(config);
}
  

// its interfaces to CANagentCORE



const embot::prot::can::applicationInfo & embot::app::application::theCANagentCORE::applicationinfo() const
{    
    return pImpl->_applicationinfo;
}

embot::hw::CAN embot::app::application::theCANagentCORE::bus() const
{ 
    return pImpl->_config.canbus;
}

embot::prot::can::Address embot::app::application::theCANagentCORE::address() const
{    
    return pImpl->_storedinfo.canaddress;
}


bool embot::app::application::theCANagentCORE::get(const embot::prot::can::bootloader::Message_BROADCAST::Info &info, embot::prot::can::bootloader::Message_BROADCAST::ReplyInfo &replyinfo) 
{   
    replyinfo.board = pImpl->_board;
    replyinfo.process = embot::prot::can::Process::application;
    replyinfo.firmware = {pImpl->_applicationinfo.version.major, pImpl->_applicationinfo.version.minor, pImpl->_applicationinfo.version.build};
                 
    return true;    
}


bool embot::app::application::theCANagentCORE::get(const embot::prot::can::bootloader::Message_GET_ADDITIONAL_INFO::Info &info, embot::prot::can::bootloader::Message_GET_ADDITIONAL_INFO::ReplyInfo &replyinfo)
{
    std::memmove(replyinfo.info32, pImpl->_storedinfo.info32, sizeof(replyinfo.info32)); 
    
    return true;
}

bool embot::app::application::theCANagentCORE::get(const embot::prot::can::shared::Message_GET_VERSION::Info &info, embot::prot::can::shared::Message_GET_VERSION::ReplyInfo &replyinfo)
{    
    replyinfo.board = pImpl->_board;
    replyinfo.firmware = {pImpl->_applicationinfo.version.major, pImpl->_applicationinfo.version.minor, pImpl->_applicationinfo.version.build};
    replyinfo.protocol = pImpl->_applicationinfo.protocol;
    
    return true;
}
    
bool embot::app::application::theCANagentCORE::get(const embot::prot::can::bootloader::Message_GET_TIMEOFLIFE::Info &info, embot::prot::can::bootloader::Message_GET_TIMEOFLIFE::ReplyInfo &replyinfo)
{
    replyinfo.timeoflife = embot::core::now();
    
    return true;
}


bool embot::app::application::theCANagentCORE::set(const embot::prot::can::bootloader::Message_BOARD::Info &info)
{
    // we just restart so we cannot reply
    embot::hw::sys::reset();
    
    return false;
}


bool embot::app::application::theCANagentCORE::set(const embot::prot::can::bootloader::Message_SET_ADDITIONAL_INFO2::Info &info)
{
    if(true == info.valid)
    {   // we have received all the 8 messages in order (important is that the one with data[1] = 0 is the first)
        embot::app::theCANboardInfo::getInstance().get(pImpl->_storedinfo);    
        std::memmove(pImpl->_storedinfo.info32, info.info32, sizeof(pImpl->_storedinfo.info32));
        embot::app::theCANboardInfo::getInstance().set(pImpl->_storedinfo);
    }   
    
    return false;
}


bool embot::app::application::theCANagentCORE::set(const embot::prot::can::shared::Message_SET_ID::Info &info)
{
    pImpl->setcanaddress(info.address, 0x0000);
    
    return false;
}


bool embot::app::application::theCANagentCORE::set(const embot::prot::can::bootloader::Message_SETCANADDRESS::Info &info)
{
    pImpl->setcanaddress(info.address, info.randominvalidmask);
    
    return false;
}



// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


