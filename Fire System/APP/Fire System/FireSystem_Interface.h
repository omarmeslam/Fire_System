

#ifndef FIRESYSTEM_INTERFACE_H_
#define FIRESYSTEM_INTERFACE_H_


void FireSystem_Init(void);
void FireSystem_Runnable(void);

typedef enum{
	STATE_1,
	STATE_2,
	STATE_3
	}SystemStates_t;


#endif /* FIRESYSTEM_INTERFACE_H_ */