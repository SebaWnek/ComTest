/*
 * timers.h
 *
 *  Created on: Apr 6, 2023
 *      Author: sebaw
 */

#ifndef INC_TIMERS_H_
#define INC_TIMERS_H_

#include <stdint.h>
#include "stm32h7xx_hal.h"

typedef void (*timerFunction)(void);

void invokeTimerFunctions(uint8_t timerNumber);
void timerStart(uint8_t timerNumber);
void timerStop(uint8_t timerNumber);
void timersInterruptHandler(TIM_HandleTypeDef *htim);
void configureTimer(TIM_HandleTypeDef *timer, uint8_t frequency, uint8_t number);
void deleteTimer(uint8_t timerNumber);

#endif /* INC_TIMERS_H_ */
