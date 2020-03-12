/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 04/02/2020               *
*********************************/
#include "..\..\LIB/01-STD_TYPES\BIT_MATH.h"
#include "..\..\LIB/01-STD_TYPES\STD_TYPES.h"
#include "GLOBAL_INT_config.h"
#include "GLOBAL_INT_interface.h"
#include "GLOBAL_INT_interface.h"
#include "GLOBAL_INT_private.h"
#include "GLOBAL_INT_register.h"
void INT_voidEnableGlobal(void)
{
	SET_BIT(SREG,SREG_I);

}
void INT_voidDisableGlobal(void)
{
	CLR_BIT(SREG,SREG_I);

}
