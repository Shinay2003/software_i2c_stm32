/*
 * I2C.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Oleh Panasiuk
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_


#include "stm32f3xx_hal.h"

//макроси для пінів SDA та SCL
#define SDA_PIN 	GPIO_PIN_2
#define SDA_PORT 	GPIOC

#define SCL_PIN 	GPIO_PIN_3
#define SCL_PORT 	GPIOC

//стандартна затримка
#define I2C_DELAY 	10

//макроси для керування лініями SDA і SCL
#define SDA_1 		HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, 1);//фронт SDA
#define SDA_0 		HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, 0);//спад  SCL

#define SCL_1 		HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, 1);//фронт SDA
#define SCL_0		HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, 0);//спад  SCL

void I2C_Start();
void I2C_Stop();
void I2C_Send_Byte(uint8_t byte);
uint8_t I2C_Receive_Byte(uint8_t ack);
void I2C_init();

#endif /* INC_I2C_H_ */
