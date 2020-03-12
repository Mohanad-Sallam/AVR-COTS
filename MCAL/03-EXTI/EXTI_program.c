/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 04/02/2020               *
*********************************/
#include "..\..\LIB/01-STD_TYPES\STD_TYPES.h"
#include "..\..\LIB/01-STD_TYPES\BIT_MATH.h"
#include "../03-EXTI/EXTI_config.h"
#include "../03-EXTI/EXTI_interface.h"
#include "../03-EXTI/EXTI_interface.h"
#include "../03-EXTI/EXTI_private.h"
#include "../03-EXTI/EXTI_register.h"
/*Global pointer to function to hold the call back address function*/
static void (*EXTI_pvCallBack[3])(void)={NULL,NULL,NULL};
void EXTI_voidInit(void)
{
#if EXTI_U8_INT0_CONTROL == ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif EXTI_U8_INT0_CONTROL == DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error "wrong EXTI_U8_INT0_CONTROL Configuration"
#endif

#if EXTI_U8_INT1_CONTROL == ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif EXTI_U8_INT1_CONTROL == DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error "wrong EXTI_U8_INT1_CONTROL Configuration"
#endif

#if EXTI_U8_INT2_CONTROL == ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif EXTI_U8_INT2_CONTROL == DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
#error "wrong EXTI_U8_INT2_CONTROL Configuration"
#endif

#if EXTI_U8_INT0_SENSE == LOW_LEVEL
	CLR_BIT (MCUCR,MCUCR_ISC00);
	CLR_BIT (MCUCR,MCUCR_ISC01);
#elif EXTI_U8_INT0_SENSE == ON_CHANGE
	SET_BIT (MCUCR,MCUCR_ISC00);
	CLR_BIT (MCUCR,MCUCR_ISC01);
#elif EXTI_U8_INT0_SENSE == FALLING_EDGE
	CLR_BIT (MCUCR,MCUCR_ISC00);
	SET_BIT (MCUCR,MCUCR_ISC01);
#elif EXTI_U8_INT0_SENSE == RISING_EDGE
	SET_BIT (MCUCR,MCUCR_ISC00);
	SET_BIT (MCUCR,MCUCR_ISC01);
#else
#error "wrong EXTI_U8_INT0_SENSE Configuration"
#endif

#if EXTI_U8_INT1_SENSE == LOW_LEVEL
	CLR_BIT (MCUCR,MCUCR_ISC10);
	CLR_BIT (MCUCR,MCUCR_ISC11);
#elif EXTI_U8_INT1_SENSE == ON_CHANGE
	SET_BIT (MCUCR,MCUCR_ISC10);
	CLR_BIT (MCUCR,MCUCR_ISC11);
#elif EXTI_U8_INT1_SENSE == FALLING_EDGE
	CLR_BIT (MCUCR,MCUCR_ISC10);
	SET_BIT (MCUCR,MCUCR_ISC11);
#elif EXTI_U8_INT1_SENSE == RISING_EDGE
	SET_BIT (MCUCR,MCUCR_ISC10);
	SET_BIT (MCUCR,MCUCR_ISC11);
#else
#error "wrong EXTI_U8_INT1_SENSE Configuration"
#endif


#if EXTI_U8_INT2_SENSE == FALLING_EDGE
	CLR_BIT (MCUCSR,MCUCSR_ISC2);
#elif EXTI_U8_INT2_SENSE == RISING_EDGE
	SET_BIT (MCUCSR,MCUCSR_ISC2);
#else
#error "wrong EXTI_U8_INT2_SENSE Configuration"
#endif
}
ErrorStatus EXTI_errEnable (u8 Copy_u8IntIdx)
{
	ErrorStatus LocalError=OK;
	switch (Copy_u8IntIdx)
	{
		case EXTI_U8_INT0: SET_BIT(GICR,GICR_INT0); break;
		case EXTI_U8_INT1: SET_BIT(GICR,GICR_INT1); break;
		case EXTI_U8_INT2: SET_BIT(GICR,GICR_INT2); break;
		default: LocalError=NOK;
	}
	return LocalError;
}
ErrorStatus EXTI_errDisable (u8 Copy_u8IntIdx)
{
	ErrorStatus LocalError=OK;
	switch (Copy_u8IntIdx)
	{
		case EXTI_U8_INT0: CLR_BIT(GICR,GICR_INT0); break;
		case EXTI_U8_INT1: CLR_BIT(GICR,GICR_INT1); break;
		case EXTI_U8_INT2: CLR_BIT(GICR,GICR_INT2); break;
		default: LocalError=NOK;
	}
	return LocalError;
}
ErrorStatus EXTI_errSetSense (u8 Copy_u8IntIdx ,u8 Copy_u8SenseLevel)
{
	ErrorStatus LocalError=OK;
	switch (Copy_u8IntIdx)
	{
		case EXTI_U8_INT0:
			switch (Copy_u8SenseLevel)
			{
			case EXTI_U8_LOW_LEVEL:
				CLR_BIT(MCUCR,MCUCR_ISC00);
				CLR_BIT(MCUCR,MCUCR_ISC01);
				break;
			case EXTI_U8_ON_CHANGE:
				SET_BIT(MCUCR,MCUCR_ISC00);
				CLR_BIT(MCUCR,MCUCR_ISC01);
				break;
			case EXTI_U8_FALLING_EDGE:
				CLR_BIT(MCUCR,MCUCR_ISC00);
				SET_BIT(MCUCR,MCUCR_ISC01);
				break;
			case EXTI_U8_RISING_EDGE:
				SET_BIT(MCUCR,MCUCR_ISC00);
				SET_BIT(MCUCR,MCUCR_ISC01);
				break;
			default:LocalError =NOK; break;
			}
			break;
		case EXTI_U8_INT1:
			switch (Copy_u8SenseLevel)
			{
			case EXTI_U8_LOW_LEVEL:
				CLR_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
				break;
			case EXTI_U8_ON_CHANGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
				break;
			case EXTI_U8_FALLING_EDGE:
				CLR_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
				break;
			case EXTI_U8_RISING_EDGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
				break;
			default:LocalError =NOK; break;
			}
			break;
		case EXTI_U8_INT2:
			switch (Copy_u8SenseLevel)
			{
			case EXTI_U8_FALLING_EDGE:
				CLR_BIT(MCUCSR,MCUCSR_ISC2);
				break;
			case EXTI_U8_RISING_EDGE:
				SET_BIT(MCUCSR,MCUCSR_ISC2);
				break;
			default:LocalError =NOK; break;
			}
			break;
		default: LocalError =NOK; break;
	}
	return LocalError;
}
ErrorStatus EXTI_errSetCalledBack (u8 Copy_u8IntIdx, void (*Copy_pvCallBack)(void))
{
	ErrorStatus LocalError=OK;
	if (Copy_pvCallBack == NULL)
	{
		LocalError =NULLPOINTER;
	}
	else
	{
		if (Copy_u8IntIdx <3)
		{
			EXTI_pvCallBack[Copy_u8IntIdx]=Copy_pvCallBack;
		}
		else
		{
			LocalError = NOK;
		}
	}
	return LocalError;
}
/*ISR of INT0*/
void __vector_1(void)
{
	if (EXTI_pvCallBack [0]!=NULL)
	{
		EXTI_pvCallBack[0]();
	}
}
/*ISR of INT1*/
void __vector_2(void)
{
	if (EXTI_pvCallBack [1]!=NULL)
	{
		EXTI_pvCallBack[1]();
	}
}
/*ISR of INT2*/
void __vector_3(void)
{
	if (EXTI_pvCallBack [2]!=NULL)
	{
		EXTI_pvCallBack[2]();
	}
}
