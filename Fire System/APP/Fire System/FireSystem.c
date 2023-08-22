#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Sensors_Interface.h"
#include "MOTOR_Interface.h"
#include "FireSystem_Cfg.h"
#include "FireSystem_Interface.h"
#include "TempFilter_Interface.h"
#include "NVM_Services.h"
#include "BCM_Services.h"



static u16 temp,smoke;
u8 TryFlag,StopFlag=0, PassIndex,PassFlag,flag,messageFlag;
static SystemStates_t state=STATE_1;
static c8 SystemPassword[10]="1234";
static c8 GetPassword[10];



static Error_t StringCompare(c8* str1, c8* str2)
{
	Error_t s=OK;
	u8 i;
	
	for (i=0; str1[i]||str2[i]; i++)
	{
		if (str1[i]!=str2[i])
		{
			s = NOK;
		}
	}
	
	return s;
}


static void PasswordEdit(void)
{
	u8 i=0,k=NO_KEY;
	
	while(k!='=')
	{
		k=KEYPAD_GetKey();
		if (k!=NO_KEY)
		{
			if (k>='0' && k<='9')
			{
				SystemPassword[i]=k;
				EEPROM_Write(i,k);
				LCD_WriteChar(k);
				i++;
			}
		}
	}
	SystemPassword[i]=0;
	EEPROM_Write(i,0);
	LCD_Clear();
	PassFlag=0;
}

static void SystemReset(void)
{
	LCD_Clear();
	DIO_WritePin(HEAT_LED,LOW);
	DIO_WritePin(FIRE_LED,LOW);	
	DIO_WritePin(BUZZER,LOW);
	MOTOR_Stop(M2);
	TryFlag = 0;
	state = STATE_1;
}




static void WriteTemp(u16 temp)
{
	LCD_GoTo(1,0);
	LCD_WriteNumber(temp/10);
	LCD_WriteChar('c');
	LCD_WriteString("  ");
}

static void WriteStateOnLCD(SystemStates_t state)
{
	LCD_GoTo(0,6);
	if (state==STATE_1)
	{
		LCD_WriteString("Fine");
	}
	else if (state==STATE_2)
	{
		LCD_WriteString("Heat");
	}
	else if (state==STATE_3)
	{
		LCD_WriteString("Fire");
	}
}






void FireSystem_Init(void)
{
	for (u8 i=0;EEPROM_Read(i)!=0;i++)
	{
		SystemPassword[i]=EEPROM_Read(i);
	}
	
	MOTOR_Stop(M2);
	DIO_WritePin(HEAT_LED,LOW);
	DIO_WritePin(FIRE_LED,LOW);
	LCD_GoTo(0,6);
	LCD_WriteString("Fine");
	
}



void FireSystem_Runnable(void)
{
	u8 k=NO_KEY;
	Error_t status=OK;
	
	temp=Filter_GetFilteredTemp();
	
	
	if (!StopFlag && !TryFlag && !PassFlag)
	{
		WriteTemp(temp);
	}
	
	if (temp>500 && (state!=STATE_3))
	{
		state = STATE_2;
	}
	else if (temp<450 && (state!=STATE_3))
	{
		state = STATE_1; 
	}
	else
	{
		/* still last state */
	}
	
	smoke=POT_Smoke_Read();
	if (temp>500 && smoke>50)
	{
		state = STATE_3;
	}
	else
	{
		/* still last state */
	}
	
	
	if (!StopFlag && !TryFlag && !PassFlag)
	{
		switch(state)
		{
			case STATE_1: /* fine state*/
			WriteStateOnLCD(state);
			LCD_GoTo(1,5);
			LCD_WriteString("Edit Pass:2");
			DIO_WritePin(HEAT_LED,LOW);
			flag=0;
			break;
			case STATE_2: /* heat state*/
			WriteStateOnLCD(state);
			LCD_GoTo(1,5);
			LCD_WriteString("Edit Pass:2");
			DIO_WritePin(HEAT_LED,HIGH);
			break;
			case STATE_3: /* fire state*/
			if (flag==0)
			{
				LCD_Clear();
				flag=1;
				messageFlag=1;
			}
			WriteStateOnLCD(state);
			LCD_GoTo(1,8);
			LCD_WriteString("Stop:1");
			DIO_WritePin(HEAT_LED,HIGH);
			DIO_WritePin(FIRE_LED,HIGH);
			DIO_WritePin(BUZZER,HIGH);
			MOTOR_CW(M2);
			if (messageFlag)
			{
				UART_SendStringAsynch("message: system is fire");
				UART_SendStringAsynch(", please fix the problem");
				messageFlag=0;
			}
			break;
			default:
			break;
		}
	}
	
	k=KEYPAD_GetKey();

	if (k=='2'&& PassFlag==0 && (state==STATE_1 || state==STATE_2))
	{
		LCD_Clear();
		LCD_GoTo(0,0);
		LCD_WriteString("Enter New Password");
		LCD_GoTo(1,0);
		PassFlag=1;
	}
	if (PassFlag==1)
	{
		PasswordEdit();
	}
	
	if (k!=NO_KEY && (state==STATE_3 || StopFlag==1))
	{
		if (k=='1' && StopFlag==0)
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteString("Enter Password");
			LCD_GoTo(1,0);
			StopFlag = 1;
			TryFlag = 1;
		}
		else if (k>='0' && k<='9' && StopFlag==1)
		{
			GetPassword[PassIndex++]=k;
			LCD_WriteChar(k);
		}
		else if (k=='=' && StopFlag==1)
		{
			status = StringCompare(GetPassword,SystemPassword);
			if (status==OK)
			{
				SystemReset();
			}
			else
			{
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteString("Wrong Password");
				LCD_GoTo(1,0);
				LCD_WriteString("1 to try again");
				TryFlag=1;
			}
			StopFlag = 0;
			PassIndex=0;
		}
	}

}

