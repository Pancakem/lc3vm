#include "cpu.h"

#define GETC 0x20
#define OUT 0x21
#define PUTS 0x22
#define IN 0x23
#define PUTSP 0x24
#define HALT 0x25


void trap_routine(cpu_t *cpu, uint16_t tv8);
