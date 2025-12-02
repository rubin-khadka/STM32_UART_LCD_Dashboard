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
    uint32_t start = DWT_CYCCNT_R;

    for(volatile int i = 0; i < 100; i++)
    {
      __NOP();
    }

    uint32_t end = DWT_CYCCNT_R;

    if(end == start)
    {
      // TODO (Rubin khadka): add error handling later
    }
  }
}

/* Delay for microseconds using DWT */
void DWT_Delay_Us(uint32_t us)
{
  uint32_t delay_cycles = us * DWT_CPU_MHZ;
  uint32_t start_cycles = DWT_CYCCNT_R;

  // Wait for required cycles
  while((DWT_CYCCNT_R - start_cycles) < delay_cycles)
  {
    // Empty
  }
}

/* Delay for milliseconds using DWT */
void DWT_Delay_Ms(uint32_t ms)
{
  while(ms--)
  {
    DWT_Delay_Us(1000); // 1000µs = 1ms
  }
}


