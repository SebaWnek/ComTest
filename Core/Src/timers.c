/*
 * timers.c
 *
 *  Created on: Apr 6, 2023
 *      Author: sebaw
 */

#include "timers.h"

#define MAX_TIMERS 2
#define MAX_FUNC_PER_TIMER 10
#define DEFAULT_PSC 999;
#define MAX_ITERATIONS 1000;

void calculateFrequency(uint16_t *arr, uint16_t *psc, uint16_t frequency);

typedef struct timerInfo
{
	uint8_t number;
	uint8_t frequency;
	TIM_HandleTypeDef *pointer;
	timerFunction functions[MAX_FUNC_PER_TIMER];
	uint8_t functionCount; //If there would be more than 255 functions here then there is definitely something wrong... But then can be changed to uint16_t if needed
} timerInfo;

static const timerInfo emptyTimer;

timerInfo timers[MAX_TIMERS] = {0};

void invokeTimerFunctions(uint8_t timerNumber)
{
	for(uint8_t i; i < timers[timerNumber].functionCount; i++)
	{
		timers[timerNumber].functions[i]();
	}
}
void timerStart(uint8_t timerNumber)
{
	HAL_TIM_Base_Start_IT(timers[timerNumber].pointer);
}
void timerStop(uint8_t timerNumber)
{
	HAL_TIM_Base_Stop_IT(timers[timerNumber].pointer);
}

void configureTimer(TIM_HandleTypeDef *timer, uint8_t frequency, uint8_t number)
{
	if (number < MAX_TIMERS)
	{
		timers[number].frequency = frequency;
		timers[number].number = number;
		timers[number].pointer = timer;
		timers[number].functionCount = 0;
		uint16_t arr, psc;
		calculateFrequency(&arr, &psc, frequency);
		timers[number].pointer->Instance->ARR = arr;
		timers[number].pointer->Instance->PSC = psc;
	}
	else
	{
		//error handler TBD
	}
}


void calculateFrequency(uint16_t *arr, uint16_t *psc, uint16_t frequency)
{
	uint32_t systemFrequency = HAL_RCC_GetSysClockFreq();
	uint32_t count = systemFrequency / frequency;
	uint32_t partA, partB, maxPart;
	partA = (uint32_t)sqrt(count);
	maxPart = partA + MAX_ITERATIONS;

	while(count % partA != 0 && partA < maxPart)
	{
		partA++;
	}
	partB = count / partA;

	if(partA > UINT16_MAX || partB > UINT16_MAX)
	{
		//error handler TBD
	}

	*arr = partA;
	*psc = partB;
}


void timersInterruptHandler(TIM_HandleTypeDef *htim)
{
	for(uint8_t i = 0; i < MAX_TIMERS; i++)
	{
		if(timers[i].pointer != NULL && htim->Instance == timers[i].pointer->Instance)
		{
			invokeTimerFunctions(i);
		}
	}
}

void deleteTimer(uint8_t timerNumber)
{
	timers[timerNumber] = emptyTimer;
}
