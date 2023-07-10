#ifndef _MEM_H_
#define _MEM_H_

#include <stdint.h>
// memory mapped registers
#define KBSR 0xFE00
#define KBDR 0xFE02

void zero_memory(uint16_t *mem);
uint16_t read_memory(uint16_t *mem, int addr);
void write_memory(uint16_t *mem, int addr, int val);

#endif
