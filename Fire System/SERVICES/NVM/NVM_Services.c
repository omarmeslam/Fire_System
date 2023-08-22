
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "NVM_Services.h"


/*************************Pointer to functions to be assigned to ISR*********************************/
static void (*EEPROM_RDY_Fptr) (void)=NULLPTR;


/*************************************************************************/
/*EEPROM Functions*/

void EEPROM_Write(u16 address, u8 data)
{
	/* Wait for completion of previous write */
	//while(READ_BIT(EECR,EEWE));
	
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;
	
	/* Write logical one to EEMWE */
	SET_BIT(EECR,EEMWE);
	
	/* Start eeprom write by setting EEWE */
	SET_BIT(EECR,EEWE);
}

u8 EEPROM_Read(u16 address)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR,EEWE));
	
	/* Set up address register */
	EEAR = address;
	
	/* Start eeprom read by writing EERE */
	SET_BIT(EECR,EERE);
	
	/* Return data from data register */
	return EEDR;
}

void EEPROM_WriteString(u16 address, u8* string)
{
	static u16 i;
	
	if (string[i])
	{
		EEPROM_Write(address+i,string[i]);
		i++;
	}
	else
	{
		EEPROM_InterruptDisable();
	}
	
}


/*********************************EEPROM Interrupt functions*********************************************/
void EEPROM_InterruptEnable(void)
{
	SET_BIT(EECR,EERIE);
}

void EEPROM_InterruptDisable(void)
{
	CLR_BIT(EECR,EERIE);
}

/*********************************EEPROM Call Back function*********************************************/
void EEPROM_RDY_SetCallBack(void(*LocalFptr)(void))
{
	EEPROM_RDY_Fptr=LocalFptr;
}


/*********************************EEPROM ISR function*********************************************/
ISR(EE_RDY_vect)
{
	if(EEPROM_RDY_Fptr!=NULLPTR)
	{
		EEPROM_RDY_Fptr();
	}
}