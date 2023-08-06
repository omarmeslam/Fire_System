

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

typedef enum{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
}ADC_VoltRef_type;


typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_type;



#define  VOLT_REF       VREF_AVCC
#define  ADC_SCALER     ADC_SCALER_64




#endif /* ADC_CFG_H_ */