/*
 * lcd16x2_control.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_LCD16X2_CONTROL_H_
#define INC_LCD16X2_CONTROL_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "lcd.h"

/* Cursor Control */
void LCD_Cursor_On(void);
void LCD_Cursor_Off(void);
void LCD_Blink_On(void);
void LCD_Blink_Off(void);
void LCD_Cursor_Blink(void);      /* Both cursor and blink ON */
void LCD_Cursor_Steady(void);     /* Cursor ON, blink OFF */

/* Display ON/OFF */
void LCD_Display_On(void);
void LCD_Display_Off(void);

/* Text Direction & Entry Mode */
void LCD_Left_To_Right(void);     /* Normal: text left → right */
void LCD_Right_To_Left(void);     /* Reverse: text right → left */
void LCD_AutoScroll_On(void);     /* Display shifts with new text */
void LCD_AutoScroll_Off(void);    /* Cursor moves, display fixed */

/* Cursor/Display Shift */
void LCD_Shift_Display_Left(void);    /* Shift entire screen left */
void LCD_Shift_Display_Right(void);   /* Shift entire screen right */
void LCD_Move_Cursor_Left(void);      /* Move cursor left only */
void LCD_Move_Cursor_Right(void);     /* Move cursor right only */

/* Utility Functions */
void LCD_Show_Cursor(uint8_t show);   /* 1=show, 0=hide */
void LCD_Set_Blink(uint8_t blink);    /* 1=blink, 0=steady */
void LCD_Set_Entry_Mode(uint8_t increment, uint8_t shift);

/* State Query Functions */
uint8_t LCD_Is_Display_On(void);
uint8_t LCD_Is_Cursor_On(void);
uint8_t LCD_Is_Blink_On(void);
uint8_t LCD_Get_Direction(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_LCD16X2_CONTROL_H_ */
