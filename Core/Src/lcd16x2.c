/*
 * lcd16x2.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Rubin Khadka
 */

#include "lcd16x2.h"
#include "main.h"
#include "dwt_config.h"

// LCD Pin Macros
#define RS(x) (x==1 ? (HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET)))
#define RW(x) (x==1 ? (HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET)))
#define EN(x) (x==1 ? (HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET)))
#define D4(x) (x==1 ? (HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET)))
#define D5(x) (x==1 ? (HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET)))
#define D6(x) (x==1 ? (HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET)))
#define D7(x) (x==1 ? (HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET)))

void lcd_init(void)
{
  // Set control pins for command mode
  RS(0); // Command mode
  RW(0); // Write mode

  // Wait for LCD power stabilization
  // Manual initialization sequence
  DWT_Delay_Ms(50);

  lcd_process_4bit(0x03);
  DWT_Delay_Ms(5);

  lcd_process_4bit(0x03);
  DWT_Delay_Us(150);

  lcd_process_4bit(0x03);
  DWT_Delay_Us(150);

  // Switch to 4 bit mode
  lcd_process_4bit(0x02);
  DWT_Delay_Us(150);

  lcd_write_command(0x28); // 4-bit, 2-line, 5x8
  lcd_write_command(0x0C); // Display ON, cursor off, blink off
  lcd_write_command(0x01); // Clear display
  DWT_Delay_Ms(2);
  lcd_write_command(0x06); // Entry mode
}

void lcd_write_command(uint8_t param)
{
  RS(0);  // Command mode
  RW(0);  // Write mode

  DWT_Delay_Us(1);

  // Send command in two 4-bit nibbles
  lcd_process_4bit(param >> 4);   // High nibble first
  lcd_process_4bit(param & 0xF);  // Low nibble second

  // Check if command needs extra delay
  if(param == 0x01 || param == 0x02)
  {
    // Clear Display or Return Home needs 1.52ms minimum
    DWT_Delay_Us(2000);  // 2ms delay for safety
  }
  else
  {
    // Other commands: need 37µs minimum
    DWT_Delay_Us(50);    // 50µs delay for safety
  }
}

void lcd_write_data(uint8_t param)
{
  RS(1);  // Data mode
  RW(0);  // Write mode

  DWT_Delay_Us(1);

  // Send data in two 4-bit nibbles
  lcd_process_4bit(param >> 4);   // High nibble first
  lcd_process_4bit(param & 0x0F); // Low nibble second

  // Data write execution delay (needs >43µs)
  DWT_Delay_Us(50);
}

void lcd_process_4bit(uint8_t data)
{
  // Set data pins using direct bit operation
  // shifted to get 1/0 value for proper macro behavior
  D4((data & 0x01) >> 0);
  D5((data & 0x02) >> 1);
  D6((data & 0x04) >> 2);
  D7((data & 0x08) >> 3);

  // Enable pulse
  EN(1);
  DWT_Delay_Us(1);
  EN(0);

  // Small delay before next operation
  DWT_Delay_Us(1);  // Wait before next operation
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
  lcd_write_command((row & 0x01) ? (0xC0 | (col & 0x0F)) : (0x80 | (col & 0x0F)));
}

void lcd_print(const char *str)
{
  while(*str)
  {
    lcd_write_data(*str++);
  }
}

void lcd_clear(void)
{
  lcd_write_command(0x01);  // Clear display command
}

