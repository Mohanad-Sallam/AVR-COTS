/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 04/02/2020               *
*********************************/
#ifndef EXTI_REGISTER_H
#define EXTI_REGISTER_H
#define MCUCR  *((volatile u8*) 0x55) /*Control register*/
#define MCUCR_ISC00  0				  /*Int0 Sense control bit0*/
#define MCUCR_ISC01  1				  /*Int0 Sense control bit1*/
#define MCUCR_ISC10  2				  /*Int1 Sense control bit0*/
#define MCUCR_ISC11  3				  /*Int1 Sense control bit1*/
#define MCUCSR *((volatile u8*) 0x54) /*Control and status register*/
#define MCUCSR_ISC2  6				  /*Int2 Sense control*/
#define GICR   *((volatile u8*) 0x5B) /*General Interrupt Control register*/
#define GICR_INT1  7				  /*Int1 Enable bit*/
#define GICR_INT0  6				  /*Int0 Enable bit*/
#define GICR_INT2  5				  /*Int2 Enable bit*/
#define GIFR   *((volatile u8*) 0x5A) /*Flag register*/
#endif
