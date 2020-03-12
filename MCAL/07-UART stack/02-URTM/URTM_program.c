#include "../../../LIB/01-STD_TYPES/BIT_MATH.h"
#include "../../../LIB/01-STD_TYPES/STD_TYPES.h"
#include "UART_interface.h"
#include "URTM_interface.h"
#include "URTM_register.h"
#include "URTM_private.h"
#include "URTM_config.h"

URTM_JobRequest URTM_QUEUE [URTM_U8_MAX_QUEUE_SIZE];
u8 URTM_QCurrent;
u8 URTM_QNext;
u8 URTM_QAvailable= URTM_U8_MAX_QUEUE_SIZE;
u8 URTM_BusyFlag =0;

u8 URTM_u8PerformJobRequest (URTM_JobRequest Copy_JobInfo)
{
  u8 Local_u8Error=ERROR_OK;
  /*check if there is an available location for the job*/
  if (URTM_QAvailable >0)
  {
  /*Add the job to the queue "Enqueue"*/
  /*Add the job to the next location*/
    URTM_QUEUE[URTM_QNext]=Copy_JobInfo;
    /*Decrement the available*/
    URTM_QAvailable--;
    /*Increment the next*/
    if (URTM_QNext == (URTM_U8_MAX_QUEUE_SIZE-1))
    {
      URTM_QNext =0;
    }
    else
    {
      URTM_QNext ++;
    }
    voidExecute();
  }
  else
  {
    Local_u8Error = ERROR_NOK;
  }
  return Local_u8Error;
}
static void  voidExecute (void)
{
  if (URTM_BusyFlag ==0)
  {
    voidStart();
  }
  else
  {
    /*Do Nothing*/
    asm ("NOP");
    
  }

}
static void voidStart(void)
{
  while (URTM_QAvailable!=URTM_U8_MAX_QUEUE_SIZE)
    /*Queue is Empty*/
  if (URTM_QAvailable==URTM_U8_MAX_QUEUE_SIZE)
  {
    URTM_BusyFlag=0;
    break;
  }
  else
  {
    /*Queue includes jobs*/
      URTM_BusyFlag=1;
      /*Start a job*/
      switch (URTM_QUEUE[URTM_QCurrent].JobType)
      {
        case URTM_SEND_SYNCH     :
        voidSendSynch();       
        break;
        case URTM_SEND_ASYNCH    :
        voidSendAsynch();       
        break;
        case URTM_RECEIVE_SYNCH  :
        voidReceiveSynch()
        break;
        case URTM_RECEIVE_ASYNCH :
        break;
      }
  }
}

static void voidSendSynch (void)
{
  u8 Local_u8Counter;
  for (Local_u8Counter =0 ; Local_u8Counter < URTM_QUEUE[URTM_QCurrent].Length; Local_u8Counter ++ )
  {
    UART_u8TransmitDataSynch ( URTM_QUEUE[URTM_QCurrent].DataBuffer[Local_u8Counter]);
  }
  URTM_QAvailable++;
  if (URTM_QCurrent == (URTM_U8_MAX_QUEUE_SIZE-1))
  {   
    URTM_QCurrent =0;
  }
  else
  {
    URTM_QCurrent ++;
  }     
}
static void voidSendAsynch(void)
{
  
} 
static void voidReceiveSynch(void)
{
  u8 Local_u8Counter;
  for (Local_u8Counter =0 ; Local_u8Counter < URTM_QUEUE[URTM_QCurrent].Length; Local_u8Counter ++ )
  {
    UART_u8ReceiveDataSynch ( URTM_QUEUE[URTM_QCurrent].DataBuffer[Local_u8Counter]);
  }
  URTM_QAvailable++;
  if (URTM_QCurrent == (URTM_U8_MAX_QUEUE_SIZE-1))
  {   
    URTM_QCurrent =0;
  }
  else
  {
    URTM_QCurrent ++;
  }     
} 
