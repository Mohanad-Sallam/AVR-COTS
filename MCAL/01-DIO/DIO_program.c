/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v03                   *
*Date: 09/02/2020               *
*********************************/
#include "..\..\LIB\01-STD_TYPES\BIT_MATH.h"
#include "..\..\LIB\01-STD_TYPES\STD_TYPES.h"
#include "../../MCAL/01-DIO/DIO_interface.h"
#include "../../MCAL/01-DIO/DIO_register.h"
#include "../../MCAL/01-DIO/DIO_private.h"
#include "../../MCAL/01-DIO/DIO_config.h"
void DIO_voidSetPortValue (u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch (Copy_u8Port)
	{
		case 'A':
		PORTA=Copy_u8Value;
		break;
		case 'B':
		PORTB=Copy_u8Value;
		break;
		case 'C':
		PORTC=Copy_u8Value;
		break;
		case 'D':
		PORTD=Copy_u8Value;
		break;
	}

}

void DIO_voidSetPinValue2 ( u8 Copy_u8Pin, u8 Copy_u8Value)
{
	u8 Local_u8ReqPort=Copy_u8Pin/8;
	u8 Local_u8ReqPin=Copy_u8Pin%8;
	switch (Local_u8ReqPort)
	{
		case 0:ASSIGN_BIT(PORTA,Local_u8ReqPin,Copy_u8Value);break;
		case 1:ASSIGN_BIT(PORTB,Local_u8ReqPin,Copy_u8Value);break;
		case 2:ASSIGN_BIT(PORTC,Local_u8ReqPin,Copy_u8Value);break;
		case 3:ASSIGN_BIT(PORTD,Local_u8ReqPin,Copy_u8Value);break;
	}
}
u8 DIO_u8GetPinValue2 (u8 Copy_u8Pin)
{
	u8 Local_u8ReqPort=Copy_u8Pin/8;
	u8 Local_u8ReqPin=Copy_u8Pin%8;
	u8 Local_u8ReqValue=-1;
	switch (Local_u8ReqPort)
	{
		case 0:Local_u8ReqValue=GET_BIT(PORTA,Local_u8ReqPin);break;
		case 1:Local_u8ReqValue=GET_BIT(PORTA,Local_u8ReqPin);break;
		case 2:Local_u8ReqValue=GET_BIT(PORTA,Local_u8ReqPin);break;
		case 3:Local_u8ReqValue=GET_BIT(PORTA,Local_u8ReqPin);break;
	}
  return Local_u8ReqValue;
}
void DIO_voidSetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	switch (Copy_u8Port)
	{
		case 'A':
		if (Copy_u8Value ==0)
		{
			CLR_BIT(PORTA,Copy_u8Pin);
		}
		else
		{
			SET_BIT(PORTA,Copy_u8Pin);
		}
		break;
		case 'B':
		if (Copy_u8Value ==0)
		{
			CLR_BIT(PORTB,Copy_u8Pin);
		}
		else
		{
			SET_BIT(PORTB,Copy_u8Pin);
		}
		break;
		case 'C':
		if (Copy_u8Value ==0)
		{
			CLR_BIT(PORTC,Copy_u8Pin);
		}
		else
		{
			SET_BIT(PORTC,Copy_u8Pin);
		}
		break;
		case 'D':
		if (Copy_u8Value ==0)
		{
			CLR_BIT(PORTD,Copy_u8Pin);
		}
		else
		{
			SET_BIT(PORTD,Copy_u8Pin);
		}
		break;
	}
}
u8 DIO_u8GetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin)
{
  switch (Copy_u8Port)
  {
    case 'A':
      return GET_BIT(PINA,Copy_u8Pin);
    case 'B':
      return GET_BIT(PINB,Copy_u8Pin);
    case 'C':
      return GET_BIT(PINC,Copy_u8Pin);
    case 'D':
      return GET_BIT(PIND,Copy_u8Pin);
  }
  return -1;
}
