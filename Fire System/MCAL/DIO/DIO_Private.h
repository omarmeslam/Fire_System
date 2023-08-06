/*
 * DIO_Private.h
 *
 * Created: 12/06/2023 00:14:15
 *  Author: OMAR
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

extern const DIO_PinStatus_type DIO_PinsStatusArr[TOTAL_PINS];
static void DIO_InitPin(DIO_Pin_type pin, DIO_PinStatus_type status);



#endif /* DIO_PRIVATE_H_ */