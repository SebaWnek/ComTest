/*
 * led_functions.c
 *
 *  Created on: Mar 12, 2023
 *      Author: sebaw
 */

#include "stm32h7xx_hal.h"
#include "led_functions.h"
#include "main.h"

void blink(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t time, uint8_t count);


void led_green_control(uint64_t input)
{
	uint8_t *data = (uint8_t*)&input;

	switch (data[0])
	{
	case '1':
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		break;
	case '0':
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		break;
	case '2':
		blink(LED_GREEN_GPIO_Port, LED_GREEN_Pin, data[1], data[2]);
		break;
	default:
		__NOP();
	}

}
void led_red_control(uint64_t input)
{
	uint8_t *data = (uint8_t*)&input;

		switch (data[0])
		{
		case '1':
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
			break;
		case '0':
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			break;
		case '2':
			blink(LED_RED_GPIO_Port, LED_RED_Pin, data[1], data[2]);
			break;
		default:
			__NOP();
		}
}
void led_yellow_control(uint64_t input)
{
	uint8_t *data = (uint8_t*)&input;

		switch (data[0])
		{
		case '1':
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
			break;
		case '0':
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
			break;
		case '2':
			blink(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, data[1], data[2]);
			break;
		default:
			__NOP();
		}
}

void blink(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t time, uint8_t count)
{
	for(uint16_t i = 0; i < 2 * count; i++)
	{
		HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
		HAL_Delay(time);
		HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
		HAL_Delay(time);
	}
}
