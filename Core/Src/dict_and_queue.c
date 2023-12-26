/*
 * dict_and_queue.c
 *
 *  Created on: Mar 11, 2023
 *      Author: sebaw
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "dict_and_queue.h"
#include "dynamic_memory.h"

#define QUEUE_SIZE 128
#define DICT_SIZE 256

typedef struct request
{
	uint8_t funcNum;
	bool isAddress;
	uint64_t data;
} request;

//as long as queue size <= 256, otherwise need to change to bigger type
static uint8_t countToExecute = 0;
static uint8_t nextFree = 0;
static uint8_t toExecute = 0;

static baseFunc dictionary[DICT_SIZE];

static request queue[QUEUE_SIZE];

void enqueue(uint8_t *data, uint32_t size)
{
	queue[nextFree].funcNum = data[0];
	if(size - 1 <= sizeof(uint64_t))
	{
		queue[nextFree].isAddress = false;
		memcpy(&queue[nextFree].data, data+1, size-1);
	}
	else
	{
		queue[nextFree].isAddress = true;
		queue[nextFree].data = (uint32_t)allocate(size-1);
		memcpy((void*)queue[nextFree].data, data+1, size-1);
	}
//	if(count == 0) //if already executing just add to queue, if not - need to set next to execution
//	{
//		toExecute = nextFree; //set newly added as next to be executed
//	}
	countToExecute++;
	if(++nextFree == QUEUE_SIZE) nextFree = 0; //need to be careful with QUEUE_SIZE = 256 when using uint8_t as this will be overflow
}

void registerFunc(baseFunc function, uint8_t position)
{
	dictionary[position] = function;
}

bool isNextReady(void)
{
	return countToExecute > 0;
}

void invokeNext(void)
{
	dictionary[queue[toExecute].funcNum](queue[toExecute].data);
	countToExecute--;
	if(++toExecute == QUEUE_SIZE) toExecute = 0; //need to be careful with QUEUE_SIZE = 256 when using uint8_t as this will be overflow
}
void invokeNow(uint8_t *data, uint32_t size)
{
	if(size - 1 <= sizeof(uint64_t))
	{
		uint64_t dataForFunc = 0;
		memcpy(&dataForFunc, &data[1], size-1);
		//dataForFunc = *(uint64_t*)&data[1];
		dictionary[data[0]](dataForFunc);
	}
	else
	{
		uint64_t dataPtr = (uint32_t)allocate(size - 1);
		memcpy((void*)dataPtr, data + 1, size - 1);
		dictionary[data[0]](dataPtr);
	}
}

void clearQueue(void)
{
	countToExecute = 0;
	toExecute = nextFree;
}
