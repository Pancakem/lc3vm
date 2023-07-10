#include "instr.h"
#include "helper.h" // for sign_extend
#include "regs.h"   // for update_flags, write_reg, RPC, R7, RCOND
#include "trap.h"   // for trap_routine
#include <stdlib.h> // for abort

uint16_t decode_instruction(uint16_t instr) { return instr >> 12; }

// ADD
void add(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t sr1 = (instr >> 6) & 0x7;
  uint16_t imm_flag = (instr >> 5) & 0x1;

  if (imm_flag) {
    uint16_t imm_val = instr & 0x1F;
    uint16_t sext_imm_val = sign_extend(imm_val, 5);
    write_reg(cpu->registers, dr, cpu->registers[sr1] + sext_imm_val);
  } else {
    uint16_t sr2 = instr & 0x7;
    write_reg(cpu->registers, dr, cpu->registers[sr1] + cpu->registers[sr2]);
  }

  update_flags(cpu->registers, dr);
}

// AND
void and (cpu_t * cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t sr1 = (instr >> 6) & 0x7;
  uint16_t imm_flag = (instr >> 5) & 0x1;

  if (imm_flag) {
    uint16_t imm_val = instr & 0x1F;
    uint16_t sext_imm_val = sign_extend(imm_val, 5);
    write_reg(cpu->registers, dr, cpu->registers[sr1] & sext_imm_val);
  } else {
    uint16_t sr2 = instr & 0x7;
    write_reg(cpu->registers, dr, cpu->registers[sr1] & cpu->registers[sr2]);
  }

  update_flags(cpu->registers, dr);
}

// BRANCH
void br(cpu_t *cpu, uint16_t instr) {
  uint16_t offset = instr & 0x1FF;
  uint16_t sext_offset = sign_extend(offset, 9);
  uint16_t cond_flag = (instr >> 9) & 0x7;

  if (cond_flag & cpu->registers[RCOND]) {
    write_reg(cpu->registers, RPC, cpu->registers[RPC] + sext_offset);
  }
}

// JUMP
void jmp(cpu_t *cpu, uint16_t instr) {
  uint16_t br = (instr >> 6) & 0x7;
  cpu->registers[RPC] = cpu->registers[br];
}

// JUMP TO SUBROUTINE
void jsr(cpu_t *cpu, uint16_t instr) {
  cpu->registers[R7] = cpu->registers[RPC];
  if ((instr >> 11) & 0x1) {
    uint16_t offset = instr & 0x7FF;
    uint16_t sext_offset = sign_extend(offset, 11);
    cpu->registers[RPC] += sext_offset; // JSR
  } else {
    uint16_t br = (instr >> 6) & 0x7;
    cpu->registers[RPC] = cpu->registers[br]; // JSSR
  }
}

// LOAD
void ld(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t offset = instr & 0x1FF;
  uint16_t sext_offset = sign_extend(offset, 9);

  cpu->registers[dr] = cpu->memory[cpu->registers[RPC] + sext_offset];
  update_flags(cpu->registers, dr);
}

// LOAD INDIRECT
void ldi(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t offset = instr & 0x1FF;
  uint16_t sext_offset = sign_extend(offset, 9);

  uint16_t indirect_pointer = cpu->registers[RPC] + sext_offset;
  uint16_t pointer = cpu->memory[indirect_pointer];
  cpu->registers[dr] = cpu->memory[pointer];
  update_flags(cpu->registers, dr);
}

// LOAD REGISTER
void ldr(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t br = (instr >> 6) & 0x7;

  uint16_t offset = instr & 0x3F;
  uint16_t sext_offset = sign_extend(offset, 6);

  cpu->registers[dr] = cpu->memory[cpu->registers[br]] + sext_offset;
  update_flags(cpu->registers, dr);
}

//  LOAD EFFECTIVE ADDRESS
void lea(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;

  uint16_t offset = instr & 0x1FF;
  uint16_t sext_offset = sign_extend(offset, 9);

  cpu->registers[dr] = cpu->registers[RPC] + sext_offset;

  update_flags(cpu->registers, dr);
}

// NOT
void not(cpu_t * cpu, uint16_t instr) {
  uint16_t sr = (instr >> 6) & 0x7;
  uint16_t dr = (instr >> 9) & 0x7;

  cpu->registers[dr] = ~cpu->registers[sr];
  update_flags(cpu->registers, dr);
}

void rti() { abort(); }

void res() { abort(); }

// STORE
void st(cpu_t *cpu, uint16_t instr) {
  uint16_t sr = (instr >> 9) & 0x7;
  uint16_t offset = instr & 0x1FF;
  uint16_t sext_offset = sign_extend(offset, 9);

  cpu->memory[cpu->registers[RPC] + sext_offset] = cpu->registers[sr];
}

// STORE INDIRECT
void sti(cpu_t *cpu, uint16_t instr) {
  uint16_t sr = (instr >> 9) & 0x7;
  uint16_t offset = instr & 0x1FF;
  uint16_t sext_offset = sign_extend(offset, 9);

  uint16_t indirect_pointer = cpu->registers[RPC] + sext_offset;
  uint16_t pointer = cpu->memory[indirect_pointer];
  cpu->memory[pointer] = cpu->registers[sr];
}

// STORE REGISTER
void str(cpu_t *cpu, uint16_t instr) {
  uint16_t sr = (instr >> 9) & 0x7;
  uint16_t br = (instr >> 6) & 0x7;

  uint16_t offset = instr & 0x3F;
  uint16_t sext_offset = sign_extend(offset, 6);

  uint16_t pointer = cpu->registers[br] + sext_offset;
  cpu->memory[pointer] = cpu->registers[sr];
}

// TRAP
void trap(cpu_t *cpu, uint16_t instr) { trap_routine(cpu, instr & 0xff); }
