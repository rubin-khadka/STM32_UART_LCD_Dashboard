/*
 * dwt_config.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Rubin Khadka
 */

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "dwt_config.h"

// DWT cycle counter
#define DWT_CYCCNT_R  (DWT->CYCCNT)

/* Initialize DWT cycle counter */
void DWT_Init(void)
{
  // Enable trace and debug
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  // Reset cycle counter
  DWT->CYCCNT = 0;

  // Enable cycle counter
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/* Delay for microseconds using DWT */
void DWT_Delay_Us(uint32_t us)
{
  uint32_t cycles = (SystemCoreClock / 1000000) * us;
  uint32_t start = DWT_CYCCNT_R;

  while((DWT_CYCCNT_R - start) < cycles);
}

/* Delay for milliseconds using DWT */
void DWT_Delay_Ms(uint32_t ms)
{
  while(ms--)
  {
    DWT_Delay_Us(1000);
  }
}

