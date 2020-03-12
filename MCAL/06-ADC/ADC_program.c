/********************************
 *Author: Mohanad Fawzy Sallam   *
 *Version: v02                   *
 *Date: 25/02/2020               *
 *********************************/
#include "..\..\LIB\01-STD_TYPES\BIT_MATH.h"
#include "..\..\LIB\01-STD_TYPES\STD_TYPES.h"
#include "../../MCAL/02-PORT/PORT_config.h"
#include "../../MCAL/02-PORT/PORT_interface.h"
#include "../../MCAL/02-PORT/PORT_private.h"
#include "../../MCAL/02-PORT/PORT_register.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"


static u16 * ADC_pu16Result=NULL;
static void (*ADC_pvCallBackNotification) (void)=NULL;
static u8 ADC_u8State=ADC_IDLE;
static u8 ADC_u8ChannelIndex=0;
static u8 ADC_u8ChainLength;
static u8 * ADC_pu8ChannelArr;
static u8 ADC_u8ISRSTATE;
void ADC_voidInit(void)
{
	/* 8 bits Mode, AVCC ref voltage, Polling(not interrupt) */

	CLR_BIT(ADMUX,7);
	SET_BIT(ADMUX,6);	//AVCC REFERENCE VOLTAGE

	SET_BIT(ADMUX,5);	//LEFT ADJUST MODE FOR 8 BITS

	SET_BIT(ADCSRA,7);	//ENABLE ADC

	SET_BIT(ADCSRA,2);	
	SET_BIT(ADCSRA,1);	//PRESCALER 128	
	SET_BIT(ADCSRA,0);	
}


u8 ADC_u8GetChannelReadingSynchronous(u8 Copy_u8Channel,u16 * Copy_pu16ADCResult)
{
	u8 Local_u8ErrorStatus= ERROR_OK;
	u32 Local_u32TimeOutCounter=0;
	if (Copy_u8Channel >31 || Copy_pu16ADCResult ==NULL)
	{
		Local_u8ErrorStatus = ERROR_NOK;
	}
	else
	{
		ADMUX&=0b11100000;
		ADMUX|=Copy_u8Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA,6);
		while((!GET_BIT(ADCSRA,4)) && (Local_u32TimeOutCounter < ADC_U32_TIMEOUT_COUNTS))
		{
			Local_u32TimeOutCounter ++;
		}
		/*check for the reason the loop is broken*/
		if (Local_u32TimeOutCounter == ADC_U32_TIMEOUT_COUNTS)
		{
			/*The loop is broken because time out passed*/
			Local_u8ErrorStatus = ERROR_TIMEOUT;
		}
		else
		{
			/*Loop is broken becaus conversion complete flag is raised*/
			SET_BIT(ADCSRA,4);
		}
#if ADC_U8_REGISTER_LENGTH==EIGHT_BITS_MODE
		*Copy_pu16ADCResult=ADCH;
#elif ADC_U8_REGISTER_LENGTH==TEN_BITS_MODE
		*Copy_pu16ADCResult=ADC;

#endif
	}
	return Local_u8ErrorStatus;
}
u8 ADC_u8GetChannelReadingAsynchronous(u8 Copy_u8Channel,u16 * Copy_pu16ADCResult,void (*Copy_pvCallBackNotification)(void))
{
	u8 Local_u8ErrorStatus=ERROR_OK;
	if (Copy_u8Channel >32 || Copy_pu16ADCResult == NULL || Copy_pvCallBackNotification == NULL)
	{
		Local_u8ErrorStatus=ERROR_NOK;
	}
	else
	{
		if (ADC_u8State == ADC_BUSY)
		{
			/*ADC is busy with previous conversion*/
			Local_u8ErrorStatus=ERROR_BUSY;
		}
		else
		{
			/*ADC is IDLE*/
			/*set ADc state to busy*/
			ADC_u8State = ADC_BUSY;
			/*make ISR be in Single channel state*/
			ADC_u8ISRSTATE=ADC_SINGLE_CHANNEL_STATE;
			/* Iniitialize the required objects*/
			ADC_pu16Result = Copy_pu16ADCResult;
			ADC_pvCallBackNotification =Copy_pvCallBackNotification;
			/*Set the reqiuired channel*/
			ADMUX&=0b11100000;
			ADMUX|=Copy_u8Channel;
			/* Start conversion*/
			SET_BIT(ADCSRA,6);
			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADCSRA,3);
		}
	}
	return Local_u8ErrorStatus;
}
u8 ADC_u8ChainInit (ADCchain_t * Copy_Chain,u8 * Copy_pu8ChannelArray,u8 Copy_u8chainLength)
{
	u8 Local_u8ErrorStatus = ERROR_OK;
	if (Copy_pu8ChannelArray == NULL)
	{
		Local_u8ErrorStatus =ERROR_NOK;

	}
	else
	{
		Copy_Chain->ChannelArr=Copy_pu8ChannelArray;
		Copy_Chain->ChainLength=Copy_u8chainLength;
	}
	return Local_u8ErrorStatus;
}
u8 ADC_u8StartChainConversion(ADCchain_t Copy_Chain,u16 * Copy_pu16Results,void (*Copy_pvCallBackNotification)(void) )
{
	u8 Local_u8ErrorStatus = ERROR_OK;
	if (Copy_Chain.ChannelArr == NULL || Copy_pu16Results == NULL || Copy_pvCallBackNotification == NULL)
	{
		Local_u8ErrorStatus =ERROR_NOK;
	}
	else
	{
		if (ADC_u8State == ADC_BUSY)
		{
			/*ADC is busy with previous conversion*/
			Local_u8ErrorStatus=ERROR_BUSY;
		}
		else
		{
			/*make ADC state busy*/
			ADC_u8State=ADC_BUSY;
			ADC_pu16Result=Copy_pu16Results;
			ADC_pvCallBackNotification=Copy_pvCallBackNotification;
			ADC_u8ChainLength=Copy_Chain.ChainLength;
			ADC_pu8ChannelArr=Copy_Chain.ChannelArr;
			ADC_u8ISRSTATE=ADC_CHAIN_STATE;
			ADC_u8ChannelIndex=0;
			/**Set the first channel */
			ADMUX &= 0b11100000;
			ADMUX |=Copy_Chain.ChannelArr[0];
			/*start conversion*/
			SET_BIT(ADCSRA,6);
			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADCSRA,3);

		}


	}
	return Local_u8ErrorStatus;

}
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if (ADC_u8ISRSTATE == ADC_SINGLE_CHANNEL_STATE)
	{
		/*get result*/
#if ADC_U8_REGISTER_LENGTH==EIGHT_BITS_MODE
		*ADC_pu16Result=ADCH;
#elif ADC_U8_REGISTER_LENGTH==TEN_BITS_MODE
		*ADC_pu16Result=ADC;
#endif
		/*Make the ADC state be IDLE*/
		ADC_u8State=ADC_IDLE;
		/*Invoke the callback function*/
		ADC_pvCallBackNotification();
		/*disable Interrupt*/
		CLR_BIT(ADCSRA,3);
	}
	else if (ADC_u8ISRSTATE == ADC_CHAIN_STATE)
	{
		/*get result*/
#if ADC_U8_REGISTER_LENGTH==EIGHT_BITS_MODE
		ADC_pu16Result[ADC_u8ChannelIndex]=ADCH;
#elif ADC_U8_REGISTER_LENGTH==TEN_BITS_MODE
		ADC_pu16Result[ADC_u8ChannelIndex]=ADC;
#endif
		ADC_u8ChannelIndex++;
		if (ADC_u8ChannelIndex == ADC_u8ChainLength)
		{
			/*chain is finished*/
			/*Make ADC state IDLE */
			ADC_u8State = ADC_IDLE;
			/*Invoke the callback function*/
			ADC_pvCallBackNotification();
			/*disable Interrupt*/
			CLR_BIT(ADCSRA,3);
		}
		else
		{
			/*switch to next channel in the chain*/
			ADMUX &= 0b11100000;
			ADMUX|= ADC_pu8ChannelArr[ADC_u8ChannelIndex];
			/*start conversion*/
			/*start conversion*/
			SET_BIT(ADCSRA,6);
		}

	}
	else
	{
		/*Do nothing*/
	}
}
