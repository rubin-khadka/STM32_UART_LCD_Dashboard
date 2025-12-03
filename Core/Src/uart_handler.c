/*
 * uart_handler.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Rubin Khadka
 */

#include "uart_handler.h"
#include "main.h"

/* Define buffer size */
#define USART1_RX_BUF_SIZE 256  // RX buffer size
#define USART1_TX_BUF_SIZE 256  // TX buffer size

/* Global buffer instances for UART*/
uint8_t usart1_rxbuf_storage[USART1_RX_BUF_SIZE];
uint8_t usart1_txbuf_storage[USART1_TX_BUF_SIZE];
volatile UART_Buffer_t usart1_rx_buf;
volatile UART_Buffer_t usart1_tx_buf;

void UART1_Init(void)
{
  // Disable UART temporarily
  USART1->CR1 &= ~USART_CR1_UE;

  // Clear any pending flags
  USART1->SR = 0;

  USART1->CR1 |= USART_CR1_RXNEIE; // Enable RX Not Empty interrupt
  // USART1->CR1 |= USART_CR1_TXEIE; // Enable TX Empty interrupt
  USART1->CR1 |= USART_CR1_TE;      // Enable transmitter
  USART1->CR1 |= USART_CR1_RE;      // Enable receiver

  // Re-enable UART
  USART1->CR1 |= USART_CR1_UE;

  // Enable interrupt in NVIC
  NVIC_EnableIRQ(USART1_IRQn);

  UART1_Buffer_Init(&usart1_rx_buf, usart1_rxbuf_storage, USART1_RX_BUF_SIZE);
  UART1_Buffer_Init(&usart1_tx_buf, usart1_txbuf_storage, USART1_TX_BUF_SIZE);
}

void UART1_Buffer_Init(volatile UART_Buffer_t *buff, uint8_t *storage, uint16_t size)
{
  buff->buffer = storage;
  buff->size = size;
  buff->head = 0;
  buff->tail = 0;
  buff->count = 0;
  buff->overflow = false;
}

bool UART1_Buffer_Full(volatile UART_Buffer_t *buff)
{
  return (buff->count >= buff->size);
}

bool UART1_Buffer_Empty(volatile UART_Buffer_t *buff)
{
  return (buff->count == 0);
}

bool UART1_Buffer_Write(volatile UART_Buffer_t *buff, uint8_t data)
{
  uint32_t primask = __get_PRIMASK();
  __disable_irq();

  if(UART1_Buffer_Full(buff))
  {
    buff->overflow = true;
    __set_PRIMASK(primask);
    return false;
  }

  buff->buffer[buff->head] = data;
  buff->head = (buff->head + 1) % buff->size;
  buff->count++;

  __set_PRIMASK(primask);

  return true;
}

uint8_t UART1_Buffer_Read(volatile UART_Buffer_t *buff)
{
  uint32_t primask = __get_PRIMASK();
  __disable_irq();

  if(UART1_Buffer_Empty(buff))
  {
    __set_PRIMASK(primask);
    return 0;
  }

  uint8_t data = buff->buffer[buff->tail];
  buff->tail = (buff->tail + 1) % buff->size;
  buff->count--;

  __set_PRIMASK(primask);
  return data;
}

/* Interrupt Functions */
void USART1_IRQHandler(void)
{
  // Check if RXNE interrupt
  if(USART1->SR & USART_SR_RXNE)
  {
    uint8_t data = USART1->DR;
    UART1_Buffer_Write(&usart1_rx_buf, data);
  }

  // TX interrupt - reads from TX buffer
  if((USART1->CR1 & USART_CR1_TXEIE) && (USART1->SR & USART_SR_TXE))
  {
    if(!UART1_Buffer_Empty(&usart1_tx_buf))
    {
      uint8_t data = UART1_Buffer_Read(&usart1_tx_buf);  // READS from TX buffer
      USART1->DR = data;
    }
  }
}

