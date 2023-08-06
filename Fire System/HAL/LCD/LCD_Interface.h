/*
 * LCD_Interface.h
 *
 * Created: 14/06/2023 15:38:07
 *  Author: OMAR
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init(void);

void LCD_Clear(void);

/**line 0:1 *cell 0"15*/
void LCD_GoTo(u8 line, u8 cell);

void LCD_WriteString(c8* str);
void LCD_WriteStringGoTo(u8 line, u8 cell, c8* str);
void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteChar(u8 ch);
void LCD_Write_4D(u16 num);

void LCD_CustomChar(u8 address, u8* pattern);
void LCD_ClearPosition(u8 line, u8 cell, u8 NoOfCells);
#endif /* LCD_INTERFACE_H_ */
