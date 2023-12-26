/*
 * dict_and_queue.h
 *
 *  Created on: Mar 11, 2023
 *      Author: sebaw
 */

#ifndef INC_DICT_AND_QUEUE_H_
#define INC_DICT_AND_QUEUE_H_

/* dictionary */

#include <stdint.h>
#include <stdbool.h>

#define ACK 0b10101010 //Acknowledge last transmission
#define ASAP 0b01010101 //Invoke emergency ASAP
#define LED1 0b01000001
#define LED2 0b01000010
#define LED3 0b01000011
#define WAIT 0b01100001

typedef void (*baseFunc)(uint64_t);

void registerFunc(baseFunc function, uint8_t position);
void enqueue(uint8_t *data, uint32_t size);
bool isNextReady(void);
void invokeNext(void);
void invokeNow(uint8_t *data, uint32_t size);
void clearQueue(void);

#endif /* INC_DICT_AND_QUEUE_H_ */
