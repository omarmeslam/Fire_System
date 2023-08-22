

#ifndef NVM_SERVICES_H_
#define NVM_SERVICES_H_

void EEPROM_Write(u16 address, u8 data);
u8 EEPROM_Read(u16 address);

void EEPROM_InterruptEnable(void);
void EEPROM_InterruptDisable(void);

void EEPROM_WriteString(u16 address, u8* string);

void EEPROM_RDY_SetCallBack(void(*LocalFptr)(void));

#endif /* NVM_SERVICES_H_ */