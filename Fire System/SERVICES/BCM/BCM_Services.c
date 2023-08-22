
#include "StdTypes.h"
#include "UART_Interface.h"


static void tx_func(void);
static c8*Str_TX_Requests[20];
static u8 noOfRequests,index_Req,StartSend;

void BCM_Init(void)
{
	UART_TX_InterruptEnable();
	UART_TX_SetCallBack(tx_func);
}


void BCM_Runnable(void)
{
	static u8 i;
	
	if ((noOfRequests>0) && (StartSend==0))
	{
		UART_Send(Str_TX_Requests[i++][0]);
		noOfRequests--;
	}
}



void UART_SendStringAsynch(c8*str)
{
	//UART_Send(str[0]);
	
	noOfRequests++;
	Str_TX_Requests[index_Req]=str;
	index_Req++;
	
}

static void tx_func(void)
{
	static u8 i,j=1;
	if (Str_TX_Requests[i][j]!=0)
	{
		UART_SendNoBlock(Str_TX_Requests[i][j]);
		j++;
		StartSend=1;
	}
	else
	{
		StartSend=0;
		i++;
		j=1;
	}
}