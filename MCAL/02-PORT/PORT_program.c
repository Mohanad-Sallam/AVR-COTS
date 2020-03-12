/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 19/01/2020               *
*********************************/
#include "..\..\LIB\01-STD_TYPES\BIT_MATH.h"
#include "..\..\LIB\01-STD_TYPES\STD_TYPES.h"
#include "../../MCAL/02-PORT/PORT_config.h"
#include "../../MCAL/02-PORT/PORT_interface.h"
#include "../../MCAL/02-PORT/PORT_private.h"
#include "../../MCAL/02-PORT/PORT_register.h"




void PORT_voidPortInitialize(void)
{
	DDRA=PORTA_DIR;
	DDRB=PORTB_DIR;
	DDRC=PORTC_DIR;
	DDRD=PORTD_DIR;

	PORTA=PORTA_INITIAL_VALUE;
	PORTB=PORTB_INITIAL_VALUE;
	PORTC=PORTC_INITIAL_VALUE;
	PORTD=PORTD_INITIAL_VALUE;
	
}
