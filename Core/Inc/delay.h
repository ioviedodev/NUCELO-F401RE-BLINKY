/*
 * delay.h
 *
 *  Created on: Sep 24, 2022
 *      Author: IOFamilia
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_
#include "stm32f4xx.h"

void delay_init(TIM_HandleTypeDef *_htim);
void delay_us (uint16_t us);

#endif /* INC_DELAY_H_ */
