
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "UART_Interface.h"
#include "UART_Cfg.h"


static void (*UART_RX_Fptr) (void)=NULLPTR;
static void (*UART_TX_Fptr) (void)=NULLPTR;

static u8 BaudRateArr[13]={207,103,51,34,25,16,12,8,6,3,1,1,0};


void UART_Init(void)
{
	ParityMode_type parity=PARITY_MODE;
	
	//boad rate
	UBRRL=BaudRateArr[BAUD_RATE];
	
	//Normal Speed
	#if SPEED==NORMAL_SPEED
	CLR_BIT(UCSRA,U2X);
	
	#elif SPEED==DOUBLE_SPEED
	SET_BIT(UCSRA,U2X);
	#endif
	
	//fram(data, parity, stop)  stop 1 , no parity , data 8-bit
	switch(parity)
	{
		case NO_Parity:
		CLR_BIT(UCSRC,UPM0);
		CLR_BIT(UCSRC,UPM1);
		break;
		case Even:
		CLR_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		break;
		case Odd:
		SET_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		break;
	}
	
	//Enable RX, TX
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}


u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

Bool_t UART_ReceivePeriodic(u8 *pdata)
{
	if (READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return TRUE;
	}
	return FALSE;
}


void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}


ISR(USART_TXC_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}

ISR(USART_RXC_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}
/*
	{
		if (ones%2==0)
		{
			parity=0;
		}
		else
		{
			parity=1;
		}
	}
	{
		if (ones%2==0)
		{
			parity=1;
		}
		else
		{
			parity=0;
		}
	}
	{
		DIO_WritePin(PIND0,READ_BIT(frame,i));
		_delay_us(104);
	}