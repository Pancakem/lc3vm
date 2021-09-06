#include "helper.h"

// registers

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define RPC 8
#define RCOND 9
#define RCOUNT 10

// condition flags
#define FL_POS (1 << 0)
#define FL_ZERO (1 << 1)
#define FL_NEG (1 << 2)

uint16_t read_reg(uint16_t *regs, unsigned short reg);
void write_reg(uint16_t *regs, unsigned short reg, uint16_t data);
void zero_regs(uint16_t *regs);
void update_flags(uint16_t *regs, uint16_t v);
