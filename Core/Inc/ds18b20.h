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

int8_t DS18B20_Initialization(GPIO_TypeDef *_DS18B20_PORT, uint16_t _DS18B20_PIN);


#endif /* INC_DS18B20_H_ */
