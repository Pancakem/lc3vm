#ifndef _INSTR_H_
#define _INSTR_H_

#include "cpu.h"
#include <stdint.h>

#define BR 0
#define ADD 1
#define LD 2
#define ST 3
#define JSR 4
#define AND 5
#define LDR 6
#define STR 7
#define RTI 8
#define NOT 9
#define LDI 10
#define STI 11
#define JMP 12
#define RES 13
#define LEA 14
#define TRAP 15

uint16_t create_mask(uint16_t from, uint16_t to);
uint16_t get_bits(uint16_t from, uint16_t to, uint16_t num);
uint16_t decode_instruction(uint16_t instr);
void add(cpu_t *cpu, uint16_t instr);
void and (cpu_t * cpu, uint16_t instr);
void br(cpu_t *cpu, uint16_t instr);
void jmp(cpu_t *cpu, uint16_t instr);
void jsr(cpu_t *cpu, uint16_t instr);
void ld(cpu_t *cpu, uint16_t instr);
void ldi(cpu_t *cpu, uint16_t instr);
void ldr(cpu_t *cpu, uint16_t instr);
void lea(cpu_t *cpu, uint16_t instr);
void not(cpu_t * cpu, uint16_t instr);
void rti();
void res();
void st(cpu_t *cpu, uint16_t instr);
void sti(cpu_t *cpu, uint16_t instr);
void str(cpu_t *cpu, uint16_t instr);
void trap(cpu_t *cpu, uint16_t instr);

#endif
