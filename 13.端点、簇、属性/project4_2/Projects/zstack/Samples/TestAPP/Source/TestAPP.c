/**************************************************************************************************
  Filename:       TestAPP.c
  Revised:        $Date: 2009-03-18 15:56:27 -0700 (Wed, 18 Mar 2009) $
  Revision:       $Revision: 19453 $

  Description:    Generic Application (no Profile).


  Copyright 2004-2009 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED 揂S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

/*********************************************************************
  This application isn't intended to do anything useful, it is
  intended to be a simple example of an application's structure.

  This application sends "Hello World" to another "Generic"
  application every 15 seconds.  The application will also
  receive "Hello World" packets.

  The "Hello World" messages are sent/received as MSG type message.

  This applications doesn't have a profile, so it handles everything
  directly - itself.

  Key control:
    SW1:
    SW2:  initiates end device binding
    SW3:
    SW4:  initiates a match description request
*********************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"

#include "TestAPP.h"
#include "DebugTrace.h"

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"
#include "UART.h"
#include"74LS164_8LED.h"
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// This list should be filled with Application specific Cluster IDs.
const cId_t TestAPP_ClusterList[TestAPP_MAX_CLUSTERS] =
{
  TestAPP_CLUSTERID
};

const SimpleDescriptionFormat_t TestAPP_SimpleDesc =
{
  TestAPP_ENDPOINT,              //  int Endpoint;
  TestAPP_PROFID,                //  uint16 AppProfId[2];
  TestAPP_DEVICEID,              //  uint16 AppDeviceId[2];
  TestAPP_DEVICE_VERSION,        //  int   AppDevVer:4;
  TestAPP_FLAGS,                 //  int   AppFlags:4;
  TestAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)TestAPP_ClusterList,  //  byte *pAppInClusterList;
  TestAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)TestAPP_ClusterList   //  byte *pAppInClusterList;
};

// This is the Endpoint/Interface description.  It is defined here, but
// filled-in in TestAPP_Init().  Another way to go would be to fill
// in the structure here and make it a "const" (in code space).  The
// way it's defined in this sample app it is define in RAM.
endPointDesc_t TestAPP_epDesc;
endPointDesc_t TestAPP_epDesc_8;

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
byte TestAPP_TaskID;   // Task ID for internal task/event processing
                          // This variable will be received when
                          // TestAPP_Init() is called.
devStates_t TestAPP_NwkState;


byte TestAPP_TransID;  // This is the unique message ID (counter)

afAddrType_t TestAPP_DstAddr;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
void TestAPP_ProcessZDOMsgs( zdoIncomingMsg_t *inMsg );
void TestAPP_HandleKeys( byte shift, byte keys );
void TestAPP_MessageMSGCB( afIncomingMSGPacket_t *pckt );
void TestAPP_SendTheMessage( void );

/*********************************************************************
 * NETWORK LAYER CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      TestAPP_Init
 *
 * @brief   Initialization function for the Generic App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notificaiton ... ).
 *
 * @param   task_id - the ID assigned by OSAL.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void TestAPP_Init( byte task_id )
{
  TestAPP_TaskID = task_id;
  TestAPP_NwkState = DEV_INIT;
  TestAPP_TransID = 0;

  // Device hardware initialization can be added here or in main() (Zmain.c).
  // If the hardware is application specific - add it here.
  // If the hardware is other parts of the device add it in main().

  TestAPP_DstAddr.addrMode = (afAddrMode_t)AddrNotPresent;
  TestAPP_DstAddr.endPoint = 0;
  TestAPP_DstAddr.addr.shortAddr = 0;

  // Fill out the endpoint description.
  
  //端点7
  TestAPP_epDesc.endPoint = 7; //TestAPP_ENDPOINT;
  TestAPP_epDesc.task_id = &TestAPP_TaskID;
  TestAPP_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&TestAPP_SimpleDesc;
  TestAPP_epDesc.latencyReq = noLatencyReqs;
  
  // Register the endpoint description with the AF
  afRegister( &TestAPP_epDesc );
  
  //端点8
  TestAPP_epDesc_8.endPoint = 8; //TestAPP_ENDPOINT;
  TestAPP_epDesc_8.task_id = &TestAPP_TaskID;
  TestAPP_epDesc_8.simpleDesc
            = (SimpleDescriptionFormat_t *)&TestAPP_SimpleDesc;
  TestAPP_epDesc_8.latencyReq = noLatencyReqs; 
  
  // Register the endpoint description with the AF
  afRegister( &TestAPP_epDesc_8 );

  // Register for all key events - This app will handle all key events
  RegisterForKeys( TestAPP_TaskID );

  // Update the display
#if defined ( LCD_SUPPORTED )
    HalLcdWriteString( "TestAPP", HAL_LCD_LINE_1 );
#endif
    
  ZDO_RegisterForZDOMsg( TestAPP_TaskID, End_Device_Bind_rsp );
  ZDO_RegisterForZDOMsg( TestAPP_TaskID, Match_Desc_rsp );
}

/*********************************************************************
 * @fn      TestAPP_ProcessEvent
 *
 * @brief   Generic Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The OSAL assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  none
 */
UINT16 TestAPP_ProcessEvent( byte task_id, UINT16 events )
{
  afIncomingMSGPacket_t *MSGpkt;
  afDataConfirm_t *afDataConfirm;

  // Data Confirmation message fields
  byte sentEP;
  ZStatus_t sentStatus;
  byte sentTransID;       // This should match the value sent
  (void)task_id;  // Intentionally unreferenced parameter

  if ( events & SYS_EVENT_MSG )
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( TestAPP_TaskID );
    while ( MSGpkt )
    {
      switch ( MSGpkt->hdr.event )
      {
        case ZDO_CB_MSG:
          TestAPP_ProcessZDOMsgs( (zdoIncomingMsg_t *)MSGpkt );
          break;
          
        case KEY_CHANGE:
          TestAPP_HandleKeys( ((keyChange_t *)MSGpkt)->state, ((keyChange_t *)MSGpkt)->keys );
          break;

        case AF_DATA_CONFIRM_CMD:
          // This message is received as a confirmation of a data packet sent.
          // The status is of ZStatus_t type [defined in ZComDef.h]
          // The message fields are defined in AF.h
          afDataConfirm = (afDataConfirm_t *)MSGpkt;
          sentEP = afDataConfirm->endpoint;
          sentStatus = afDataConfirm->hdr.status;
          sentTransID = afDataConfirm->transID;
          (void)sentEP;
          (void)sentTransID;

          // Action taken when confirmation is received.
          if ( sentStatus != ZSuccess )
          {
            // The data wasn't delivered -- Do something
          }
          break;

        case AF_INCOMING_MSG_CMD:
          TestAPP_MessageMSGCB( MSGpkt );
          break;

        case ZDO_STATE_CHANGE:
          TestAPP_NwkState = (devStates_t)(MSGpkt->hdr.status);
          
          if (TestAPP_NwkState == DEV_ZB_COORD){
              //协调器
              LS164_BYTE(11);
          }

          if (TestAPP_NwkState == DEV_ROUTER){
              //路由器
              LS164_BYTE(12);
          }
              
          if (TestAPP_NwkState == DEV_END_DEVICE){
              //终端
              LS164_BYTE(13); 
          }   
          break;
        default:
          break;
      }

      // Release the memory
      osal_msg_deallocate( (uint8 *)MSGpkt );

      // Next
      MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( TestAPP_TaskID );
    }

    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }

  // Send a message out - This event is generated by a timer
  //  (setup in TestAPP_Init()).
  if ( events & TestAPP_SEND_MSG_EVT ){
      
    P0DIR |= 0X02;
    P0_1 = 0;
      
    // return unprocessed events
    return (events ^ TestAPP_SEND_MSG_EVT);
  }
  
  
  if ( events & TestAPP_EVT ){
     
     P0SEL &=0XEF;//1110 1111 
     P0DIR |= 0X10;
     P0_4 ^= 1;
     
     if(0==P1_1){/*按钮3按下*/LS164_BYTE(3);}
     if(0==P2_0){/*按钮4按下*/LS164_BYTE(4);}
     if(0==P0_5){/*按钮5按下*/LS164_BYTE(5);}
      
     return (events ^ TestAPP_EVT);
  }

  // Discard unknown events
  return 0;
}

/*********************************************************************
 * Event Generation Functions
 */

/*********************************************************************
 * @fn      TestAPP_ProcessZDOMsgs()
 *
 * @brief   Process response messages
 *
 * @param   none
 *
 * @return  none
 */
void TestAPP_ProcessZDOMsgs( zdoIncomingMsg_t *inMsg )
{
  switch ( inMsg->clusterID )
  {
    case End_Device_Bind_rsp:
      if ( ZDO_ParseBindRsp( inMsg ) == ZSuccess )
      {
        // Light LED
        HalLedSet( HAL_LED_4, HAL_LED_MODE_ON );
      }
#if defined(BLINK_LEDS)
      else
      {
        // Flash LED to show failure
        HalLedSet ( HAL_LED_4, HAL_LED_MODE_FLASH );
      }
#endif
      break;

    case Match_Desc_rsp:
      {
        ZDO_ActiveEndpointRsp_t *pRsp = ZDO_ParseEPListRsp( inMsg );
        if ( pRsp )
        {
          if ( pRsp->status == ZSuccess && pRsp->cnt )
          {
            TestAPP_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
            TestAPP_DstAddr.addr.shortAddr = pRsp->nwkAddr;
            // Take the first endpoint, Can be changed to search through endpoints
            TestAPP_DstAddr.endPoint = pRsp->epList[0];

            // Light LED
            HalLedSet( HAL_LED_4, HAL_LED_MODE_ON );
          }
          osal_mem_free( pRsp );
        }
      }
      break;
  }
}

/*********************************************************************
 * @fn      TestAPP_HandleKeys
 *
 * @brief   Handles all key events for this device.
 *
 * @param   shift - true if in shift/alt.
 * @param   keys - bit field for key events. Valid entries:
 *                 HAL_KEY_SW_4
 *                 HAL_KEY_SW_3
 *                 HAL_KEY_SW_2
 *                 HAL_KEY_SW_1
 *
 * @return  none
 */
void TestAPP_HandleKeys( byte shift, byte keys )
{
   LS164_BYTE(keys);
}

/*********************************************************************
 * LOCAL FUNCTIONS
 */

/*********************************************************************
 * @fn      TestAPP_MessageMSGCB
 *
 * @brief   Data message processor callback.  This function processes
 *          any incoming data - probably from other devices.  So, based
 *          on cluster ID, perform the intended action.
 *
 * @param   none
 *
 * @return  none
 */
void TestAPP_MessageMSGCB( afIncomingMSGPacket_t *pkt )
{
   // 端点7
   if(7 == pkt->endPoint){
      switch(pkt->clusterId){// 判断是哪个簇
         case 0x0001:
            LS164_BYTE(pkt->cmd.Data[0]);
            P1SEL &=0XFE;//1111 1110  LED1
            P1DIR |=0X01;//
            P1_0 ^=1;
            break;
           
         case 0x0002:
            LS164_BYTE(pkt->cmd.Data[0]);
            P0SEL &=0XFD;// 1111 1101;
            P0DIR |=0X02;
            P0_1 ^=1;
            break;
      }
   }
   
   // 端点8
   if(8 == pkt->endPoint){
      switch(pkt->clusterId){
         case 0x0001:
            LS164_BYTE(pkt->cmd.Data[0]);
            P0SEL &=0XEF;// 1110 1111 LED3
            P0DIR |=0X10;
            P0_4 ^=1;
            break;
      }
   }
}

/*********************************************************************
 * @fn      TestAPP_SendTheMessage
 *
 * @brief   Send "the" message.
 *
 * @param   none
 *
 * @return  none
 */
void TestAPP_SendTheMessage( void )
{
  char theMessageData[] = "Hello World";

  if ( AF_DataRequest( &TestAPP_DstAddr, &TestAPP_epDesc,
                       TestAPP_CLUSTERID,
                       (byte)osal_strlen( theMessageData ) + 1,
                       (byte *)&theMessageData,
                       &TestAPP_TransID,
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS ) == afStatus_SUCCESS )
  {
    // Successfully requested to be sent.
  }
  else
  {
    // Error occurred in request to send.
  }
}

/*********************************************************************
*********************************************************************/
