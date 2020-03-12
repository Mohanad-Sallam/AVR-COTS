/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 04/02/2020               *
*********************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
#define EXTI_U8_INT0 0
#define EXTI_U8_INT1 1
#define EXTI_U8_INT2 2

#define EXTI_U8_LOW_LEVEL    0
#define EXTI_U8_ON_CHANGE    1
#define EXTI_U8_FALLING_EDGE 2
#define EXTI_U8_RISING_EDGE  3

/*
 * Description: Function used to initialize the External Interrupts INT0, INT1, Int2 according to the
 * Precompiled Configuration.
 * Inputs:  void
 * Outputs: void
 * */
void EXTI_voidInit(void);
/*
 * Description: Function used to Enable the priephral enable of External Interrupts INT0, INT1, INT2
 * Inputs:  Interrupt Index, Ranges are
 * 			1- EXTI_U8_INT0
 * 			2- EXTI_U8_INT1
 * 			3- EXTI_U8_INT2
 * Outputs: Error Status
 * */
ErrorStatus EXTI_errEnable (u8 Copy_u8IntIdx);
/*
 * Description: Function used to Disable the priephral enable of External Interrupts INT0, INT1, INT2
 * Inputs:  Interrupt Index, Ranges are
 * 			1- EXTI_U8_INT0
 * 			2- EXTI_U8_INT1
 * 			3- EXTI_U8_INT2
 * Outputs: Error Status
 * */
ErrorStatus EXTI_errDisable (u8 Copy_u8IntIdx);
/*
 * Description: Function used to Set the required sense level of INT0,INT1,INT2
 * Inputs:	1-Interrupt Index, Ranges are
 * 				1- EXTI_U8_INT0
 * 				2- EXTI_U8_INT1
 * 				3- EXTI_U8_INT2
 * 			2-Sense Levels:
 * 				1- EXTI_U8_LOW_LEVEL
 * 				2- EXTI_U8_ON_CHANGE
 * 				3- EXTI_U8_FALLING_EDGE
 * 				4- EXTI_U8_RISING_EDGE
 * Outputs: Error Status
 * */
ErrorStatus EXTI_errSetSense (u8 Copy_u8IntIdx ,u8 Copy_u8SenseLevel);
/*
 * Description: Function used to Set theCall Back function of INT0,INT1,INT2
 * Inputs:	1-Interrupt Index, Ranges are
 * 				1- EXTI_U8_INT0
 * 				2- EXTI_U8_INT1
 * 				3- EXTI_U8_INT2
 * 			2- CallBack Function to the required address of application ISR function
 * Outputs: Error Status
 * */
ErrorStatus EXTI_errSetCalledBack (u8 Copy_u8IntIdx, void (*Copy_pvCallBack)(void));
#endif
