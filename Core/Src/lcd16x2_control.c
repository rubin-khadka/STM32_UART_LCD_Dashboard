/*
 * lcd16x2_control.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Rubin Khadka
 */

#include "lcd16x2_control.h"

void LCD_Cursor_On(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->cursor_on = 1;
  LCD_Update_Control_Register();
}

void LCD_Cursor_Off(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->cursor_on = 0;
  LCD_Update_Control_Register();
}

void LCD_Blink_On(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->blink_on = 1;
  LCD_Update_Control_Register();
}

void LCD_Blink_Off(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->blink_on = 0;
  LCD_Update_Control_Register();
}

void LCD_Cursor_Blink(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->cursor_on = 1;
  state->blink_on = 1;
  LCD_Update_Control_Register();
}

void LCD_Cursor_Steady(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->cursor_on = 1;
  state->blink_on = 0;
  LCD_Update_Control_Register();
}

void LCD_Display_On(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->display_on = 1;
  LCD_Update_Control_Register();
}

void LCD_Display_Off(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->display_on = 0;
  LCD_Update_Control_Register();
}

void LCD_Left_To_Right(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->entry_mode = (state->entry_mode & 0x01) | 0x02;
  state->direction = 0;
  LCD_Update_Entry_Mode();
}

void LCD_Right_To_Left(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->entry_mode = state->entry_mode & 0x01;  // Clear bit 1
  state->direction = 1;
  LCD_Update_Entry_Mode();
}

void LCD_AutoScroll_On(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->entry_mode = (state->entry_mode & 0x02) | 0x01;
  LCD_Update_Entry_Mode();
}

void LCD_AutoScroll_Off(void)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->entry_mode = state->entry_mode & 0x02;  // Clear bit 0
  LCD_Update_Entry_Mode();
}

void LCD_Shift_Display_Left(void)
{
  LCD_Write_Command(0x18);  // Shift display left command
  DWT_Delay_Us(50);
}

void LCD_Shift_Display_Right(void)
{
  LCD_Write_Command(0x1C);  // Shift display right command
  DWT_Delay_Us(50);
}

void LCD_Move_Cursor_Left(void)
{
  LCD_Write_Command(0x10);  // Move cursor left command
  DWT_Delay_Us(50);
}

void LCD_Move_Cursor_Right(void)
{
  LCD_Write_Command(0x14);  // Move cursor right command
  DWT_Delay_Us(50);
}

void LCD_Show_Cursor(uint8_t show)
{
  if(show)
  {
    LCD_Cursor_On();
  }
  else
  {
    LCD_Cursor_Off();
  }
}

void LCD_Set_Blink(uint8_t blink)
{
  if(blink)
  {
    LCD_Blink_On();
  }
  else
  {
    LCD_Blink_Off();
  }
}

void LCD_Set_Entry_Mode(uint8_t increment, uint8_t shift)
{
  LCD_Control_State_t *state = LCD_Get_State();
  state->entry_mode = (increment ? 0x02 : 0x00) | (shift ? 0x01 : 0x00);
  LCD_Update_Entry_Mode();

  // Update direction flag
  state->direction = increment ? 0 : 1;
}

uint8_t LCD_Is_Display_On(void)
{
  return LCD_Get_State()->display_on;
}

uint8_t LCD_Is_Cursor_On(void)
{
  return LCD_Get_State()->cursor_on;
}

uint8_t LCD_Is_Blink_On(void)
{
  return LCD_Get_State()->blink_on;
}

uint8_t LCD_Get_Direction(void)
{
  return LCD_Get_State()->direction;
}
