/*
 * uart_handler.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_UART_HANDLER_H_
#define INC_UART_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

/* Circular buffer structure for UART */
typedef struct
{
  uint8_t          *buffer; // Pointer to buffer memory
  uint16_t          size;   // Total buffer size
  volatile uint16_t head;   // Write Position
  volatile uint16_t tail;   // Read Position
  volatile uint16_t count;  // Number of bytes in the buffer
  volatile bool     overflow;   // Overflow flag
} UART_Buffer_t;

/* External declarations */
extern volatile UART_Buffer_t usart1_rx_buf;
extern volatile UART_Buffer_t usart1_tx_buf;

/* Function Definition */
void UART1_Init(void);

/* Core buffer functions */
void UART1_Buffer_Init(volatile UART_Buffer_t *buff, uint8_t *storage, uint16_t size);
bool UART1_Buffer_Full(volatile UART_Buffer_t *buff);
bool UART1_Buffer_Empty(volatile UART_Buffer_t *buff);
bool UART1_Buffer_Write(volatile UART_Buffer_t *buff, uint8_t data);
uint8_t UART1_Buffer_Read(volatile UART_Buffer_t *buff);

void USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_UART_HANDLER_H_ */
