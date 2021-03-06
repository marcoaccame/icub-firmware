/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
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
#ifndef _EOVTHEIPNET_H_
#define _EOVTHEIPNET_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @file       EOVtheIPnet.h
    @brief      This header file implements public interface to the virtual IP net singleton.
    @author     marco.accame@iit.it
    @date       08/24/2011
**/

/** @defgroup eov_theipnet Singleton EOVtheIPnet
    The EOVtheIPnet allows ...... 
    
    The EOVtheIPnet has pure virtual functions ....
    @todo acemor-facenda: do documentation.
    
    @{        
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "EoCommon.h"
#include "EOsocket.h"
#include "EOVtask.h"


// - public #define  --------------------------------------------------------------------------------------------------
// empty-section
  

// - declaration of public user-defined types ------------------------------------------------------------------------- 
 

/** @typedef    typedef struct EOVtheIPnet_hid EOVtheIPnet
    @brief      EOVtheIPnet is an opaque struct. It is used to implement data abstraction for the IP net 
                object so that the user cannot see its private fields and he/she is forced to manipulate the
                object only with the proper public functions. 
 **/  
typedef struct EOVtheIPnet_hid EOVtheIPnet;


/** @typedef    typedef void EOVtheIPnetDerived
    @brief      EOVtheIPnetDerived is used to implement polymorphism in the objects derived from EOVtheIPnet
 **/
typedef void EOVtheIPnetDerived;


//extern const eOevent_t  eok_ipnet_evt_RXipframe;        /**< = 0x00000001;  */
//extern const eOevent_t  eok_ipnet_evt_CMD2process;      /**< = 0x00000002;  */
//extern const eOevent_t  eok_ipnet_evt_CMD2stop;         /**< = 0x00000004;  */
//extern const eOevent_t  eok_ipnet_evt_TXdatagram;       /**< = 0x00000008;  */
//extern const eOevent_t  eok_ipnet_evt_evalRXipframe;    /**< = 0x00000010;  */
//extern const eOevent_t  eok_ipnet_evt_tick;             /**< = 0x00000020;  */

typedef enum
{
    eov_ipnet_evt_tick                  = 0x00000001,   /**< used to produce a run of the ipnet loop. the effect of a run depends on implementions */   
    eov_ipnet_evt_RXethframe            = 0x00000002,   /**< used to alert the ipnet about the reception of an IP frame. it is the ISR of ETH to alert */
    eov_ipnet_evt_CMD2process           = 0x00000004,   /**< used to alert the ipnet about the start of processing of a command */
    eov_ipnet_evt_CMD2stop              = 0x00000008,   /**< used to alert the ipnet about the end of processing of a command */
    eov_ipnet_evt_TXdatagram            = 0x00000010    /**< used to alert the ipnet about the presence of a datagram to transmit. it is a socket or the ipnet to alert */
} eOv_ipnet_event_t;


//#define     EOK_ipnet_evt_RXipframe         0x00000001
//#define     EOK_ipnet_evt_CMD2process       0x00000002
//#define     EOK_ipnet_evt_CMD2stop          0x00000004
//#define     EOK_ipnet_evt_TXdatagram        0x00000008
//#define     EOK_ipnet_evt_evalRXipframes    0x00000010
//#define     EOK_ipnet_evt_tick              0x00000020


    
// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------
// empty-section


// - declaration of extern public functions ---------------------------------------------------------------------------
 
 
/** @fn         extern EOVtheIPnet* eov_eov_ipnet_GetHandle(void)
    @brief      Returns an handle to the singleton EOVtheIPnet.  The singleton must have been initialised by
                the Initialise() method of a derived type, otherwise this function call will return NULL.
    @return     The pointer to the required EOVtheIPnet (or NULL upon in-initialised singleton).
 **/
extern EOVtheIPnet* eov_ipnet_GetHandle(void);

extern eOresult_t eov_ipnet_Activate(EOVtheIPnet *p);

extern eOresult_t eov_ipnet_Deactivate(EOVtheIPnet *p);


/** @fn         extern eOpurevirtual eOresult_t eov_ eov_ipnet_AttachSocket(EOVtheIPnet* p, EOdatagramSocket *s)
    @brief      Attach a datagram socket to the ip manager. The function is to be called only by a method of
                EOdatagramSocket (or EOstreamSocket when and if available).
    @param      p               The pointer to the ip net singleton. 
    @param      t               The pointer to the datagram socket. 
    @return     cecece
    @todo       document return and explain how long it takes control of the socket
 **/
extern eOresult_t eov_ipnet_AttachSocket(EOVtheIPnet* p, EOsocketDerived *s);


/** @fn         extern eOresult_t eov_eov_ipnet_DetachSocket(EOVtheIPnet* p, EOdatagramSocket *s)
    @brief      Detach a datagram socket from the ip manager. The function is to be called only by a method of
                EOdatagramSocket (or EOstreamSocket when and if available).
    @param      p               The pointer to the ip net singleton. 
    @param      t               The pointer to the datagram socket. 
    @return     cecece
    @todo       document return
 **/
extern eOresult_t eov_ipnet_DetachSocket(EOVtheIPnet* p, EOsocketDerived *s);


/** @fn         extern eOresult_t eov_eov_ipnet_Alert(EOVtheIPnet* p, eOevent_t evt)
    @brief      Send an event to the ip manager. The function is to be called only by a method of
                EOdatagramSocket (or EOstreamSocket when and if available) or by the ethernet ISR. 
    @param      p               The pointer to the timer manager singleton. 
    @param      evt             The event as a single bit. does not work if it is a mask. 
    @return     cecece
    @todo       document return
 **/
extern eOpurevirtual eOresult_t eov_ipnet_Alert(EOVtheIPnet* p, void *eobjcaller, eOevent_t evt);


extern eOpurevirtual eOresult_t eov_ipnet_ResolveIP(EOVtheIPnet* p, eOipv4addr_t ipaddr, eOreltime_t tout);


extern eOpurevirtual eOresult_t eov_ipnet_WaitPacket(EOVtheIPnet* p, EOsocketDerived *s, eOreltime_t tout);


extern eOresult_t eov_ipnet_IGMPgroupJoin(EOVtheIPnet* p, eOipv4addr_t igmpgroup);


extern eOresult_t eov_ipnet_IGMPgroupLeave(EOVtheIPnet* p, eOipv4addr_t igmpgroup);


extern void eov_ipnet_DisableSynTx(EOVtheIPnet* p, uint8_t skttag);


extern void eov_ipnet_EnableSynTx(EOVtheIPnet* p, uint8_t skttag);


/** @}            
    end of group eov_theipnet 
 **/

#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 

#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



