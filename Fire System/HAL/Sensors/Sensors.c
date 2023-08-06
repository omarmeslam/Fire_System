
#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"


u16 Interpolation_Fun(u16 sen_low,u16 sen_high,u16 adc_low, u16 adc_high,u16 adc_read)
{
	u16 sen_result, sen_diff, adc_diff;
	
	sen_diff = 10*(sen_high-sen_low);
	adc_diff = adc_high-adc_low;
	
	sen_result = (( ((u32)sen_diff*adc_read)-((u32)sen_diff*adc_low))/adc_diff)+(sen_low*10);
	
	return sen_result;
}

u16 TEMP_Read(void)
{
	u16 volt=ADC_VoltRead(LM35_CH);
	u16 temp;
	
	temp = volt;
	
	return temp;
}

u16 Pressure_Read(void)
{
	u16 adc=ADC_Read(MPX4115);
	u16 pressure;
	
	pressure = Interpolation_Fun(MPX_LOW_PRESSURE,MPX_MAX_PRESSURE,MPX_LOW_ADC,MPX_MAX_ADC,adc);
	return pressure;
}

u16 Smoke_Read(void)
{
	u16 adc=ADC_Read(MPX4115);
	u16 smoke;
	
	smoke = Interpolation_Fun(MPX_LOW_PRESSURE,MPX_MAX_PRESSURE,MPX_LOW_ADC,MPX_MAX_ADC,adc);
	return smoke;
}



u16 POT_Temp_Read(void)
{
	u16 pot,percentage;
	
	pot = ADC_Read(POT_TEMP_CH);
	percentage = ((u32)pot*100)/1023;
	return percentage;
}


u16 POT_Smoke_Read(void)
{
	u16 pot,percentage;
	
	pot = ADC_Read(POT_PRESS_CH);
	percentage = ((u32)pot*100)/1023;
	return percentage;
}