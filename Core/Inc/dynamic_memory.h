/*
 * dynamic_memory.h
 *
 *  Created on: Mar 11, 2023
 *      Author: sebaw
 */

#ifndef INC_DYNAMIC_MEMORY_H_
#define INC_DYNAMIC_MEMORY_H_

/* Allocates size bytes for temporary storage that is over 8 bytes large
 * Works in circular way, overwrites oldest data assuming it was already processed
 * Buffer size should be large enough to make sure no data will be overwritten too early
 * As H7 has enough RAM - decided this will be easier and faster than implementing additional free function
 */
uint8_t* allocate(uint32_t size);

#endif /* INC_DYNAMIC_MEMORY_H_ */
