/*
 * gpio.h
 *
 *  Created on: Sep 24, 2022
 *      Author: IOFamilia
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

void GPIO_Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* INC_GPIO_H_ */
