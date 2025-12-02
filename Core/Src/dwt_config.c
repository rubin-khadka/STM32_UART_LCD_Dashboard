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
#define DWT_CYCCNT_R  (*(volatile uint32_t *)&DWT->CYCCNT)

/* Initialize DWT cycle counter */
void DWT_Init(void)
{
  // Check if DWT is already enabled
  if(!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))
  {
    // Enable Trace
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Reset cycle counter to 0
    DWT->CYCCNT = 0;

    // Enable cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    // Verify DWT is actually counting
    uint32_t start = DWT_CYCLE_COUNT();

    for(volatile int i = 0; i < 10; i++);
    if(DWT_CYCCNT_R == start)
    {
      // DWT failed to start - handle error
    }
  }
}

//
void DWT_Delay_Us(uint32_t us)
{
  // Calculate cycles needed
  uint32_t cycles_per_us = SystemCoreClock / 1000000;
  if(cycles_per_us == 0)
  {
    cycles_per_us = 1; // Safety
  }

  uint32_t delay_cycles = us * cycles_per_us;
  uint32_t start_cycles = DWT_CYCCNT_R;

  // Wait for required cycles
  while((DWT_CYCCNT_R - start_cycles) < delay_cycles)
  {
    // Empty
  }
}

