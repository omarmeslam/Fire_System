
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Cfg.h"
#include "MOTOR_Interface.h"


	


void MOTOR_Init(void)
{
	MOTOR_type i;
	for(i=M1; i<TOTAL_MOTORS; i++)
	{
		MOTOR_Stop(i);
	}
}

void MOTOR_Stop(MOTOR_type m)
{
	DIO_WritePin(MotorPinsArr[m][0], LOW);
	DIO_WritePin(MotorPinsArr[m][1], LOW);	
	
}
void MOTOR_CW(MOTOR_type m)
{
	DIO_WritePin(MotorPinsArr[m][0], LOW);
	DIO_WritePin(MotorPinsArr[m][1], HIGH);
}
void MOTOR_CCW(MOTOR_type m)
{
	DIO_WritePin(MotorPinsArr[m][0], HIGH);
	DIO_WritePin(MotorPinsArr[m][1], LOW);
}