/*
 * lcd16x2.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_LCD16X2_H_
#define INC_LCD16X2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

// LCD Function prototypes
void LCD_Init(void);
void LCD_Write_Command(uint8_t param);
void LCD_Write_Data(uint8_t param);
void LCD_Process_4Bit(uint8_t data);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Print(const char *);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_EntryMode_Set(uint8_t mode);
void LCD_DisplayControl_Set(uint8_t ctrl);
void LCD_Shift(uint8_t shift_type);
void LCD_Set_CGRAM_Addr(uint8_t addr);

#ifdef __cplusplus
}
#endif

#endif /* INC_LCD16X2_H_ */
