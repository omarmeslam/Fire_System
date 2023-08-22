 


#ifndef UART_CFG_H_
#define UART_CFG_H_

typedef enum{
	BR_2400=0,
	BR_4800,
	BR_9600,
	BR_14k4,
	BR_19k2,
	BR_28k8,
	BR_38k4,
	BR_57k6,
	BR_76k8,
	BR_115k2,
	BR_230k4,
	BR_250k,
	BR_05M
}BaudRate_type;

#define BAUD_RATE  BR_9600

typedef enum{
	NO_Parity,
	Even,
	Odd
	}ParityMode_type;
 
#define  PARITY_MODE  NO_Parity



/* select the type of speed */
#define  NORMAL_SPEED  1
#define  DOUBLE_SPEED  2

#define  SPEED  NORMAL_SPEED

#endif /* UART_CFG_H_ */