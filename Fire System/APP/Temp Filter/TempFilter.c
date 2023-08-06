#include "StdTypes.h"
#include "Sensors_Interface.h"
#include "FireSystem_Interface.h"

#define   FILTER_TEMP_SIZE   10

u16 FILTER_TempArr[FILTER_TEMP_SIZE];
u16 FILTER_FilteredTemp;
u16 FILTER_UnFilteredTemp;

void Filter_Init(void)
{
	u16 TempInit=POT_Temp_Read();
	FILTER_UnFilteredTemp=TempInit;
	
	for (u8 i=0;i<FILTER_TEMP_SIZE;i++)
	{
		FILTER_TempArr[i]=TempInit;
	}
}


void Filter_Runnable(void)
{
	static u8 in=0;
	u16 tempsum=0;

	FILTER_TempArr[in] = POT_Temp_Read();
	FILTER_UnFilteredTemp = FILTER_TempArr[in];
	in++;
	if (in==10)
	{
		in=0;
	}

	for (u8 j=0;j<FILTER_TEMP_SIZE;j++)
	{
		tempsum += FILTER_TempArr[j];
	}
	
	FILTER_FilteredTemp = tempsum/FILTER_TEMP_SIZE;
	
}

u16 Filter_GetFilteredTemp(void)
{
	return FILTER_FilteredTemp;
}



u16 Filter_GetUnFilteredTemp(void)
{
	return FILTER_UnFilteredTemp;
}