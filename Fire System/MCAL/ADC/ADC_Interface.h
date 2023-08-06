

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	CH_0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;

void ADC_Init(void);

u16 ADC_Read(ADC_Channel_type CH);

/*return mv*/
u16 ADC_VoltRead(ADC_Channel_type CH);

void ADC_StartConversion(ADC_Channel_type CH);
u16 ADC_GetRead(void);
Bool_t ADC_GetReadPerodic(u16* pdata);
u16 ADC_GetReadNoBlock(void);

#endif /* ADC_INTERFACE_H_ */