/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 04/02/2020               *
*********************************/
#ifndef GLOBAL_INT_REGISTER_H
#define GLOBAL_INT_REGISTER_H
#define SREG *((volatile u8*) 0x5F) /*status register*/
#define SREG_I 7
#endif
