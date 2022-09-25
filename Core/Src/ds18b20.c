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
#include "stdbool.h"

GPIO_TypeDef *	DS18B20_PORT;
uint16_t 		DS18B20_PIN;
bool			ds18b20_initialized;

int8_t DS18B20_Initialization(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN)
{
	int8_t Response = 0;
	DS18B20_PORT=_DS18B20_PORT;
	DS18B20_PIN=_DS18B20_PIN;
	ds18b20_initialized = true;

	GPIO_Set_Pin_Output(_DS18B20_PORT, _DS18B20_PIN);   // Set the pin as output
	HAL_GPIO_WritePin (_DS18B20_PORT, _DS18B20_PIN, 0);  //BUS MASTER PULLING LOW
	delay_us(M_RESET_PULSE_MINIMUN);   //Delay according to datasheet M_RESET_PULSE_MINIMUN

	GPIO_Set_Pin_Input(_DS18B20_PORT, _DS18B20_PIN); // Set the pin as input
	delay_us(S_PRESENCE_PULSE);    //Delay according to datasheet


	if (!(HAL_GPIO_ReadPin (_DS18B20_PORT, _DS18B20_PIN))) Response = SUCCESS;    //Check if the pin is low in that case the presence pulse is detected
	else Response = INITIALIZATION_FAIL;

	delay_us (M_RX_MINIMUN-S_PRESENCE_PULSE);

	return Response;
}


int8_t DS18B20_write(uint8_t _bit)
{
	if(!ds18b20_initialized) return NO_INITIALIZED;

	if(_bit==0)
	{
		HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);
		delay_us(M_WRITE_0_WAIT);
	}
	else
	{
		HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);
		delay_us(M_WRITE_1_WAIT);
		HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 1);
		delay_us(M_WRITE_1_KEPT);
	}

	return 0;
}

int8_t DS18B20_read(void)
{
	delay_us(M_READ_WAIT);
	if(!HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
	{//Tent to be zero
		delay_us(M_READ_KEPT);
		if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
		{//Confirm is zero
			return READED_ZERO;
		}
		else
			return NO_VALID_READING;
	}
	else
	{//Tent to be one
		delay_us(M_READ_KEPT);
		if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
		{//Confirm is one
			return READED_ONE;
		}
		else
			return NO_VALID_READING;
	}

}

