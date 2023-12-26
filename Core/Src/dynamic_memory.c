/*
 * dynamic_memory.c
 *
 *  Created on: Mar 11, 2023
 *      Author: sebaw
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 10240

static uint8_t memBuffer[BUFFER_SIZE];

uint32_t lastFree = 0;

bool isEnoughSpaceLeft(uint32_t size);


uint8_t* allocate(uint32_t size)
{
	uint8_t *result = NULL;
	if(size > BUFFER_SIZE)
		return result;

	if(isEnoughSpaceLeft(size))
	{
		result = memBuffer + lastFree;
		lastFree += size;
	}
	else
	{
		result = memBuffer;
		lastFree = size;
	}
	return result;
}

bool isEnoughSpaceLeft(uint32_t size)
{
	return size < BUFFER_SIZE - lastFree;
}
