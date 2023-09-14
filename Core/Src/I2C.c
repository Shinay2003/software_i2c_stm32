/*
 * I2C.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Oleh Panasiuk
 */
#include "I2C.h"

//функція ініціалізації i2c
void I2C_Init()
{
    // Ініціалізація GPIOC SDA і SCL як вивідних пінів
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SDA_PIN | SCL_PIN;//аналогічні настройки для SCL та SDA
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;//відкритий колектор
    GPIO_InitStruct.Pull = GPIO_NOPULL;//без використання підтягуючих резисторів
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;//висока частота зміни
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

// Початок передачі
void I2C_Start()
{
    SDA_0 //низький стан для початку роботи інтерфейсу
    HAL_Delay(I2C_DELAY);
    SCL_0;
}

// Зупинка передачі/
void I2C_Stop()
{
    SDA_0
	HAL_Delay(I2C_DELAY);
    SCL_1
    HAL_Delay(I2C_DELAY);
    SDA_1
}

// Відправка байта
void I2C_Send_Byte(uint8_t byte)
{
	//цикл для відправки байта
    for (int i = 7; i >= 0; i--)
    {
        if (byte & (1 << i))
        {
           SDA_1
        }
        else
        {
            SDA_0
        }
        SCL_1
        HAL_Delay(I2C_DELAY);
        SCL_0
        HAL_Delay(I2C_DELAY);
    }
    // Очікування підтвердження
    SDA_1
    SCL_1
    while (HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN));
    SCL_0
}

// Отримання байта
//в аргументах вказуємо останній біт(ack/nack 1/0), який відповідає чи Master очікує ще дані
//чи передача буде закінчена
uint8_t I2C_Receive_Byte(uint8_t ack)
{
    uint8_t byte = 0;
    SDA_1
    for (int i = 7; i >= 0; i--)
    {
        SCL_1
        if (HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN))
        {
            byte |= (1 << i);
        }
        HAL_Delay(I2C_DELAY);
        SCL_0
        HAL_Delay(I2C_DELAY);
    }
    //перевірка останнього біта
    if (ack)
    {
        SDA_0
    }
    else
    {
       SDA_1
    }
    SCL_1
    HAL_Delay(I2C_DELAY);
    SCL_0
    HAL_Delay(I2C_DELAY);
    return byte;
}
