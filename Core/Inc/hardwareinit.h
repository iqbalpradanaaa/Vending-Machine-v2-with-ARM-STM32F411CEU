/*
 * hardwareinit.h
 *
 *  Created on: Dec 8, 2020
 *      Author: ACER
 */

#ifndef INC_HARDWAREINIT_H_
#define INC_HARDWAREINIT_H_

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_TIM2_Init(uint32_t Periode);

#endif /* INC_HARDWAREINIT_H_ */
