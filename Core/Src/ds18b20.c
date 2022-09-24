/*
 * ds18b20.c
 *
 *  Created on: Sep 24, 2022
 *      Author: IOFamilia
 */
#include "stdint.h"
#include "delay.h"
#include "gpio.h"
#include "ds18b20.h"
#include "codes.h"
#include "stm32f4xx.h"

int8_t DS18B20_Initialization(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN)
{
	int8_t Response = 0;

	GPIO_Set_Pin_Output(_DS18B20_PORT, _DS18B20_PIN);   // Set the pin as output
	HAL_GPIO_WritePin (_DS18B20_PORT, _DS18B20_PIN, 0);  //BUS MASTER PULLING LOW
	delay_us(M_RESET_PULSE_MINIMUN);   //Delay according to datasheet

	GPIO_Set_Pin_Input(_DS18B20_PORT, _DS18B20_PIN); // Set the pin as input
	delay_us(S_PRESENCE_PULSE);    //Delay according to datasheet

	if (!(HAL_GPIO_ReadPin (_DS18B20_PORT, _DS18B20_PIN))) Response = SUCCESS;    //Check if the pin is low in that case the presence pulse is detected
	else Response = INITIALIZATION_FAIL;

	delay_us (M_RX_MINIMUN-S_PRESENCE_PULSE);

	return Response;
}
