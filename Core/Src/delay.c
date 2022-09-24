/*
 * delay.c
 *
 *  Created on: Sep 24, 2022
 *      Author: IOFamilia
 */
#include "stdint.h"
#include "stm32f4xx.h"

TIM_HandleTypeDef *htim;

void delay_init(TIM_HandleTypeDef *_htim)
{
	htim=_htim;
}

void delay_us (uint16_t _us)
{
	__HAL_TIM_SET_COUNTER(htim,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(htim) < _us);  // wait for the counter to reach the us input in the parameter
}
