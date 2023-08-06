
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#include "Utils.h"

#define F_CPU 8000000
#include <util/delay.h>


#if LCD_MODE==_8_BIT

static void WriteIns(u8 ins)
{
	DIO_WritePin(RS, LOW);
	DIO_WritePort(LCD_PORT, ins);
	DIO_WritePin(E, HIGH);
	_delay_ms(1);
	DIO_WritePin(E, LOW);
	_delay_ms(1);
}

void WriteData(u8 data)
{
	DIO_WritePin(RS, HIGH);
	DIO_WritePort(LCD_PORT, data);
	DIO_WritePin(E, HIGH);
	_delay_ms(1);
	DIO_WritePin(E, LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x38);
	WriteIns(0x0C);
	WriteIns(0x01); //clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#else

static void WriteIns(u8 ins)
{
	DIO_WritePin(RS, LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(E, HIGH);
	_delay_ms(1);
	DIO_WritePin(E, LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(E, HIGH);
	_delay_ms(1);
	DIO_WritePin(E, LOW);
	_delay_ms(1);
}

void WriteData(u8 data)
{
	DIO_WritePin(RS, HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	
	DIO_WritePin(E, HIGH);
	_delay_ms(1);
	DIO_WritePin(E, LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(E, HIGH);
	_delay_ms(1);
	DIO_WritePin(E, LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0C);
	WriteIns(0x01); //clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#endif

void LCD_Clear(void)
{
	WriteIns(0x01);
}

void LCD_GoTo(u8 line, u8 cell)
{
	if(line==0)
	{
		WriteIns(0x80+cell);
	}
	else if (line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
}


void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(c8* str)
{
	u8 i;
	for(i=0; str[i]; i++)
	{
		LCD_WriteChar(str[i]);
	}
}

void LCD_WriteNumber(s32 num)
{
	c8 str[16];	
	u8 i=0;
	s8 j=0;
	 
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if(num<0)
	{
		LCD_WriteChar('-');
		num = num * -1;
	}
	
	while(num)
	{
		str[i++] = num%10 +'0';
		num = num/10;
	}
	
	for(j=i-1; j>=0; j--)
	{
		LCD_WriteChar(str[j]);
	}
	
	
}

void LCD_Write_4D(u16 num) //5214
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7; i>=0; i--)
	{
		if(((num>>i)&1)==1)
		{
			LCD_WriteChar('1');
		}
		else
		{
			LCD_WriteChar('0');
		}
		//LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}

void LCD_WriteHex(u8 num)
{
	u8 d0,d1;
	d0=num&0x0F;
	d1=(num>>4)&0x0F;
	
	if(d1<10)
	{
		LCD_WriteChar(d1+'0');
	}
	else
	{
		LCD_WriteChar(d1-10+'A');
	}
	
	if(d0<10)
	{
		LCD_WriteChar(d0+'0');
	}
	else
	{
		LCD_WriteChar(d0-10+'A');
	}
}

void LCD_WriteStringGoTo(u8 line, u8 cell, c8* str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}

void LCD_ClearPosition(u8 line, u8 cell, u8 NoOfCells)
{
	u8 i;
	LCD_GoTo(line,cell);
	for(i=0; i<NoOfCells; i++)
	{
		LCD_WriteChar(' ');
	}
}


void LCD_CustomChar(u8 address, u8* pattern)
{
	u8 i;
	
	WriteIns(0x40+address*8);
	for(i=0; i<8; i++)
	{	
		LCD_WriteChar(pattern[i]);
	}
	WriteIns(0x80);
}