/*
 * ds18b20.h
 *
 *  Created on: Sep 24, 2022
 *      Author: IOFamilia
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include "stdint.h"
#include "stm32f4xx.h"

//TIMES CHECK DATASHEET DS18B20
#define M_RESET_PULSE_MINIMUN	480
#define S_PRESENCE_PULSE		60  // Value between 60-240 uS
#define M_RX_MINIMUN			480
#define M_WRITE_0_WAIT			60
#define M_WRITE_1_WAIT			1
#define M_WRITE_1_KEPT			50	//<=60uS
#define M_READ_MINIMUN_TS		60	//<=60uS
#define M_READ_WAIT				14  //<=15uS
#define M_READ_KEPT				40  //<=45uS
#define M_READ_MINIMUN_TS		60
#define M_READ_RECOVERY			1

#define SIZE_BYTE_IN_BITS		8

typedef enum
{
	reading,
	writing,
	no_configure
}pin_mode;

int8_t DS18B20_Initialization(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN);
int8_t DS18B20_write_byte(uint8_t _byte_data);
int8_t DS18B20_read_byte(void);

#endif /* INC_DS18B20_H_ */
