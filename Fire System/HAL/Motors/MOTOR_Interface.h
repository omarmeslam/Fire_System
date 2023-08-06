


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


typedef enum{
	M1,
	M2,
	M3,
	M4,
	TOTAL_MOTORS
}MOTOR_type;

void MOTOR_Init(void);
void MOTOR_Stop(MOTOR_type m);
void MOTOR_CW(MOTOR_type m);
void MOTOR_CCW(MOTOR_type m);

/* speed 0:100*/
/* speed 0:1400*/
void MOTOR_Speed(MOTOR_type m,u8 speed);

#endif /* MOTOR_INTERFACE_H_ */