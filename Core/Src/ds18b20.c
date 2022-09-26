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
pin_mode		current_pin_mode;

void DS18B20_dq_change_mode(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN, pin_mode _mode);

int8_t DS18B20_Initialization(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN)
{
	int8_t Response = 0;
	DS18B20_PORT=_DS18B20_PORT;
	DS18B20_PIN=_DS18B20_PIN;
	ds18b20_initialized = true;

	DS18B20_dq_change_mode(_DS18B20_PORT, _DS18B20_PIN, writing);
	HAL_GPIO_WritePin (_DS18B20_PORT, _DS18B20_PIN, 0);  //BUS MASTER PULLING LOW
	delay_us(M_RESET_PULSE_MINIMUN);   //Delay according to datasheet M_RESET_PULSE_MINIMUN

	DS18B20_dq_change_mode(_DS18B20_PORT, _DS18B20_PIN, reading);
	delay_us(S_PRESENCE_PULSE);    //Delay according to datasheet


	if (!(HAL_GPIO_ReadPin (_DS18B20_PORT, _DS18B20_PIN))) Response = SUCCESS;    //Check if the pin is low in that case the presence pulse is detected
	else Response = INITIALIZATION_FAIL;

	delay_us (M_RX_MINIMUN-S_PRESENCE_PULSE);

	return Response;
}


int8_t DS18B20_write_byte(uint8_t _byte_data)
{
	uint8_t index_bit=0;
	uint16_t mask=0;

	DS18B20_dq_change_mode(DS18B20_PORT, DS18B20_PIN, writing);
	if(!ds18b20_initialized) return NO_INITIALIZED;

	for(index_bit=0; index_bit<SIZE_BYTE_IN_BITS; index_bit++)
	{
		mask=1<<index_bit;
		DS18B20_dq_change_mode(DS18B20_PORT, DS18B20_PIN, writing);
		if((_byte_data & mask)==mask)
		{// write one bit
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);
			delay_us(M_RECOVERY_TIME+M_WRITE_1_KEPT_TS);
		}
		else
		{//write zero bit
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);
			delay_us(M_RECOVERY_TIME+M_WRITE_0_WAIT);
		}
		DS18B20_dq_change_mode(DS18B20_PORT, DS18B20_PIN, reading);//It takes 9uS
		delay_us(M_READ_MINIMUN_TS);
	}
	DS18B20_dq_change_mode(DS18B20_PORT, DS18B20_PIN, reading);
	return SUCCESS;
}

int16_t DS18B20_read_byte(void)
{
	uint16_t index_bit=0;
	int16_t data_byte=0;

	if(!ds18b20_initialized) return NO_INITIALIZED;

	for (index_bit=0; index_bit<SIZE_BYTE_IN_BITS; index_bit++)
	{
		if(current_pin_mode!=writing)
			DS18B20_dq_change_mode(DS18B20_PORT, DS18B20_PIN, writing);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN,0);
		delay_us(M_READ_RECOVERY);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
		DS18B20_dq_change_mode(DS18B20_PORT, DS18B20_PIN, reading);
		delay_us(M_READ_WAIT-5);//Fix uTimes
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
		if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
		{
			data_byte |= 1<<index_bit;  // read = 1
		}

		delay_us(M_READ_MINIMUN_TS);
	}

	return data_byte;
}


void DS18B20_dq_change_mode(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN, pin_mode _mode)
{
	if(_mode==reading)
	{
		GPIO_Set_Pin_Input(_DS18B20_PORT, _DS18B20_PIN); // Set the pin as input
	}
	else
	{
		GPIO_Set_Pin_Output(_DS18B20_PORT, _DS18B20_PIN); // Set the pin as output
	}
	current_pin_mode=_mode;
}
