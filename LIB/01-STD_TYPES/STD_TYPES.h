/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v03                   *
*Date: 09/03/2020               *
*********************************/
#ifndef STD_TYPES_H_H_
#define STD_TYPES_H_H_
typedef unsigned char u8 ;
typedef signed char  s8;
typedef  unsigned short int u16;
typedef  signed short int s16;
typedef  unsigned long int u32;
typedef  signed long int s32;
typedef  float f32;
typedef  double f64;

typedef  u8* pu8 ;
typedef   s8* ps8;
typedef   u16* pu16;
typedef   s16* ps16;
typedef   u32* pu32;
typedef  s32* ps32;
typedef   f32* pf32;
typedef   f64* pf64;

typedef enum Error
{
	OK,
	NOK,
	NULLPOINTER
}ErrorStatus;
#define ERROR_OK 0
#define ERROR_NOK 1
#define ERROR_TIMEOUT 2
#define ERROR_BUSY 3

#define NULL ((void*)0)

#endif
