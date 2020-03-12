#include "../../LIB/01-STD_TYPES/BIT_MATH.h"
#include "../../LIB/01-STD_TYPES/STD_TYPES.h"
#include "UART_interface.h"
#include "UART_register.h"
#include "UART_private.h"
#include "UART_config.h"
const u8 BaudRateValue [3][3]={
  /*4800 , 9600 ,  115200*/
  { 0x67 , 0x33 , 0x03   }, /*clk system 0 = 8MHZ */
  { 154  , 77   , 6      }, /*clk system 1 = 12MHZ */
  { 0xcf , 0x67 , 0x08   }  /*clk system 2 = 16MHZ */
};
void (*EndOfTransmitCB)(void);
void (*EndOfReceiveCB)(u8);
void UART_voidInitialize (void)
{
    /*u2x=0*/
    CLR_BIT (UCSRA,1);
    /*Enable Tx and Rx*/
    /*Data size = 8-bit*/
    UCSRB=0x18;
    /*Parity select*/
    /*UCSRC&=0xCF;*/
    UCSRC=((1<<7) |(UART_U8_PARITY <<4) | (UART_U8_STOP_BITS <<3) | (3<<1)) ;
    /*Assign Baud Rate Value*/
    UBRRL= BaudRateValue[UART_U8_SYS_FREQ][UART_U8_BAUD_RATE];
}
u8 UART_u8TransmitDataSynch (u8 Copy_u8Data)
{
    u8 Local_u8Error=ERROR_OK;
    u32 Local_u32TimeOut=0;
    /*Send data on UDR*/
    UDR_T = Copy_u8Data;
    /*wait till flag is raised*/
    while ((!GET_BIT(UCSRA,6))&&Local_u32TimeOut < UART_U32_TIME_OUT_THRESHOLD)
    {
      Local_u32TimeOut ++;
    }
    /*Time out happened*/
    if (Local_u32TimeOut >= UART_U32_TIME_OUT_THRESHOLD)
    {
      Local_u8Error=ERROR_TIMEOUT;
    }
    else
    {
      SET_BIT(UCSRA,6);
    }
    return Local_u8Error;
}
void UART_voidTransmitDataAsynch (u8 Copy_u8Data,void (*Copy_ptr)(void))
{
  /*Enable Interrupt*/
  SET_BIT(UCSRB,6);
  /*set received data to UDR_T*/
  UDR_T= Copy_u8Data;
  /*save the callback address*/
  EndOfTransmitCB=Copy_ptr;
  
}
u8 UART_u8ReceiveDataSynch (u8 * Copy_pu8Data)
{
    u8 Local_u8Error=ERROR_OK;
    u32 Local_u32TimeOut=0;
    /*Send data on UDR*/

    /*wait till flag is raised*/
    while ( (GET_BIT(UCSRA,7)==0) && (Local_u32TimeOut < UART_U32_TIME_OUT_THRESHOLD) )
    {
      Local_u32TimeOut ++;
    }
    /*Time out happened*/
    if (Local_u32TimeOut >= UART_U32_TIME_OUT_THRESHOLD)
    {
      Local_u8Error=ERROR_TIMEOUT;
    }
    else
    {      
      *Copy_pu8Data = UDR_R;
    }
    return Local_u8Error;
}
void UART_u8ReceiveDataASynch (void (*Copy_ptr)(u8))
{
  /*check if there is a data to receive*/
  if (GET_BIT(UCSRA,7))
  {
    Copy_ptr(UDR_R);
  }
    /*Nothing to receive now*/
  else
  {
    /*Enable Interrupt*/
    SET_BIT(UCSRB,7);
    /*save callback in global value*/
    EndOfReceiveCB=Copy_ptr;
  }
}
