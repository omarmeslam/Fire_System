/*
 * MOTOR_Cfg.h
 *
 * Created: 12/06/2023 13:39:44
 *  Author: OMAR
 */ 


#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/*********************PIN CONFIG *************************/

#define  M1_IN1   PINC0
#define  M1_IN2   PINC1

#define  M2_IN1   PINC2
#define  M2_IN2   PINC3


#define  M3_IN1   PINC4
#define  M3_IN2   PINC5


#define  M4_IN1   PINC6
#define  M4_IN2   PINC7

DIO_Pin_type MotorPinsArr[4][2]={{M1_IN1,M1_IN2},
					   			 {M2_IN1,M2_IN2},
								 {M3_IN1,M3_IN2},
								 {M4_IN1,M4_IN2}};

#endif /* MOTOR_CFG_H_ */