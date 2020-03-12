#include "../../LIB/01-STD_TYPES/BIT_MATH.h"
#include "../../LIB/01-STD_TYPES/STD_TYPES.h"
#include "Delay.h"
/*loop time (T1)=5.39875 us*/
/*calculation time (T2)=627.875 us*/
/*context switching time (T3)=3.995 us*/
/*context switching time (T4)=2.255 us*/


/*void Delay_ms(u32 time)
{
	const u32 ctr = time * 666;
	for (volatile u32 c = 0; c < ctr; c++)
	{

	}
}*/
#define T1 (0.00539875f)
#define TM (0.634125f)
/*loop time (T1)=5.39875 us*/
/*calculation time (T2)=627.875 us*/
/*context switching time (T3)=3.995 us*/
/*context switching time (T4)=2.255 us*/
void Delay_ms(u32 Val)
{
  u32 i;
u32 count =   (u32)((float)Val-TM)/T1;
for (i=0;i<count;i++)
{
  asm("NOP");
}
}

void Delay_us(u32 time)
{
	const u32 ctr = (time * 666) / 1000;
	for (volatile u32 c = 0; c < ctr; c++)
	{

	}
}
