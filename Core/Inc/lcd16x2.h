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
void lcd_init(void);
void lcd_write_command(uint8_t param);
void lcd_write_data(uint8_t param);
void lcd_process_4bit(uint8_t data);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *);
void lcd_clear(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_LCD16X2_H_ */
