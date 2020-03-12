/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 25/02/2020               *
*********************************/
typedef struct
{
	u8 * ChannelArr;
	u8  ChainLength;

}ADCchain_t;
void ADC_voidInit(void);
u8 ADC_u8GetChannelReadingSynchronous(u8 Copy_u8Channel,u16 * Copy_pu16ADCResult);
u8 ADC_u8GetChannelReadingAsynchronous(u8 Copy_u8Channel,u16 * Copy_pu16ADCResult,void (*Copy_pvCallBackNotification)(void));
u8 ADC_u8ChainInit (ADCchain_t * Copy_Chain,u8 * Copy_pu8ChannelArray,u8 Copy_u8chainLength);
