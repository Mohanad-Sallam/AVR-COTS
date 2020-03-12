/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v02                   *
*Date: 04/02/2020               *
*********************************/
#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H
/*
 * Options: 1-Enabled
 * 			2-Disabled
 * */
#define EXTI_U8_INT0_CONTROL ENABLED

/*
 * Options: 1-Enabled
 * 			2-Disabled
 * */
#define EXTI_U8_INT1_CONTROL ENABLED

/*
 * Options: 1-Enabled
 * 			2-Disabled
 * */
#define EXTI_U8_INT2_CONTROL DISABLED

/*
 * Options: 1-LOW_LEVEL
 * 			2-ON_CHANGE
 * 			3-FALLING_EDGE
 * 			4-RISING_EDGE
 * */
#define EXTI_U8_INT0_SENSE RISING_EDGE

/*
 * Options: 1-LOW_LEVEL
 * 			2-ON_CHANGE
 * 			3-FALLING_EDGE
 * 			4-RISING_EDGE
 * */
#define EXTI_U8_INT1_SENSE FALLING_EDGE

/*
 * Options: 1-FALLING_EDGE
 * 			2-RISING_EDGE
 * */
#define EXTI_U8_INT2_SENSE FALLING_EDGE

#endif
