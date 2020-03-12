/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 24/02/2020               *
*********************************/
#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H
void Timer0_voidInit(void);
void Timer0_voidSetCallBack(void(*Copy_pvCallBackPtr)(void));
#endif