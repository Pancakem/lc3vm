#include "regs.h"

uint16_t read_reg(uint16_t *regs, unsigned short reg) {
  return read_data(regs, reg);
}

void write_reg(uint16_t *regs, unsigned short reg, uint16_t data){
  write_data(regs, reg, data);
}

void zero_regs(uint16_t *regs){
  zero_data_region(regs, RCOUNT);
}

void update_flags(uint16_t *regs, uint16_t r)
{
    if (regs[r] == 0) {
        regs[RCOND] = FL_ZERO;
    }
    else if (regs[r] >> 15) {
        regs[RCOND] = FL_NEG;
    }
    else {
        regs[RCOND] = FL_POS;
    }
}
