/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v01                   *
*Date: 09/03/2020               *
********************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void UART_voidInitialize (void);
u8 UART_u8TransmitDataSynch (u8 Copy_u8Data);
void UART_voidTransmitDataAsynch (u8 Copy_u8Data,void (*Copy_ptr)(void));
u8 UART_u8ReceiveDataSynch (u8 * Copy_pu8Data);
void UART_u8ReceiveDataASynch (void (*Copy_ptr)(u8));

#endif