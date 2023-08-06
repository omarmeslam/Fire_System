
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"
#include "ADC_Cfg.h"

#define F_CPU 8000000
#include <util/delay.h>

static u8 ADC_BusyFlag;

void ADC_Init(void)
{
	ADC_VoltRef_type vref = VOLT_REF;
	ADC_Prescaler_type scaler = ADC_SCALER;
	/* vref*/

	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	
	/* prescaller*/
	
	ADCSRA &= 0xF8;
	scaler &= 0x07;
	ADCSRA = ADCSRA | ADC_SCALER;
	
	/* enable ADC*/
	SET_BIT(ADCSRA,ADEN);
	
}




u16 ADC_Read(ADC_Channel_type CH)
{
	u16 adc=0;
	
	/* set channel mux*/ 
	ADMUX &= 0xE0;
	ADMUX = ADMUX | CH;
	
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	
	/* w8 ADC finish busy wait (blocking) */
	while(READ_BIT(ADCSRA,ADSC));
	
	/*get read*/
	adc = ADCL;
	adc = adc | (ADCH<<8);
	
	return adc;
}

void ADC_StartConversion(ADC_Channel_type CH)
{
	if (ADC_BusyFlag==0)
	{
		/* set channel mux*/
		ADMUX &= 0xE0;
		ADMUX = ADMUX | CH;
		
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_BusyFlag=1;
	}
	
}

u16 adc=0;
u16 ADC_GetRead(void)
{
	
	/*get read*/
	
	/* w8 ADC finish busy wait (blocking) */
	while(READ_BIT(ADCSRA,ADSC));
	
	adc = ADCL;
	adc = adc | (ADCH<<8);
	
	return adc;
}


Bool_t ADC_GetReadPerodic(u16* pdata)
{
	/* perodic check (polling) */
	if (!READ_BIT(ADCSRA,ADSC))
	{
		*pdata=adc;
		ADC_BusyFlag=0;
		return TRUE;
	}
	return FALSE;
}


u16 ADC_GetReadNoBlock(void)
{
	u16 adc = ADCL;
	adc = adc | (ADCH<<8);
	
	return adc;
}





u16 ADC_VoltRead(ADC_Channel_type CH)
{
	u16 adc,volt;
	
	adc=ADC_Read(CH);
	volt=((u32)adc*5000)/1024;
	
	return volt;
}