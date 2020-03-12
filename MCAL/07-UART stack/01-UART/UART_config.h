/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v01                   *
*Date: 09/03/2020               *
********************************/
#ifndef UART_CONFIG_H
#define UART_CONFIG_H

/*Options : UART_PARITY_DISABLED
            UART_PARITY_EVEN
            UART_PARITY_ODD*/
#define UART_U8_PARITY  UART_PARITY_DISABLED

/*Options : UART_BAUD_4800
            UART_BAUD_9600
            UART_BAUD_115200*/
#define UART_U8_BAUD_RATE  UART_BAUD_9600 
/*Options : UART_STOP_1_BIT
            UART_STOP_2_BIT*/
#define UART_U8_STOP_BITS UART_STOP_1_BIT 
/*Options : UART_SYS_FREQ_8M
            UART_SYS_FREQ_12M
            UART_SYS_FREQ_16M*/
#define UART_U8_SYS_FREQ UART_SYS_FREQ_8M
#define  UART_U32_TIME_OUT_THRESHOLD 1000
#endif