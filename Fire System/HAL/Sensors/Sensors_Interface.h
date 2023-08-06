


#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_


/* temp with c*10 */
u16 TEMP_Read(void);

u16 Pressure_Read(void);

u16 Smoke_Read(void);

u16 POT_Temp_Read(void);
u16 POT_Smoke_Read(void);

u16 Interpolation_Fun(u16 sensor_low,u16 sensor_high,u16 adc_low, u16 adc_high,u16 adc_result);



#endif /* SENSORS_INTERFACE_H_ */