/*
 * dwt_config.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Rubin Khadka
 */

#ifndef INC_DWT_CONFIG_H_
#define INC_DWT_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#ifndef DWT_CPU_MHZ
#define DWT_CPU_MHZ 72  //Configured to 72 MHz
#endif

/* Function Definitions */
void DWT_Init(void);
void DWT_Delay_Us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* INC_DWT_CONFIG_H_ */
