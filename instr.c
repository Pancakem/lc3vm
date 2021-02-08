#include "instr.h"

uint16_t decode_instruction(uint16_t instr) {
  return instr >> 12;
}

void add(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t sr1 = (instr >> 6) & 0x7;
  uint16_t imm_flag = (instr >> 5) & 0x1;
  
  if (imm_flag) {
    write_reg(cpu->registers, dr, cpu->registers[sr1] + sign_extend(instr & 0x1F, 5));
  }
  else {
    uint16_t sr2 = instr & 0x7;
    write_reg(cpu->registers, dr, cpu->registers[sr1] + cpu->registers[sr2]); 
  }

  update_flags(cpu->registers, dr);
}

void and(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t sr1 = (instr >> 6) & 0x7;
  uint16_t imm_flag = (instr >> 5) & 0x1;
  
  if (imm_flag) {
    write_reg(cpu->registers, dr, cpu->registers[sr1] & sign_extend(instr & 0x1F, 5));
  }
  else {
    uint16_t sr2 = instr & 0x7;
    write_reg(cpu->registers, dr, cpu->registers[sr1] & cpu->registers[sr2]); 
  }
  
  update_flags(cpu->registers, dr);
}

void br(cpu_t *cpu, uint16_t instr) {
  uint16_t offset = sign_extend(instr & 0x1ff, 9);
  uint16_t cond_flag = (instr >> 9) && 0x7;
  
  if (cond_flag & cpu->registers[RCOND]){
    write_reg(cpu->registers, RPC, cpu->registers[RPC] + offset);
  }
}

void jmp(cpu_t *cpu, uint16_t instr) {
  uint16_t br = (instr >> 6) & 0x7;
  cpu->registers[RPC] = cpu->registers[br];
}

void jsr(cpu_t *cpu, uint16_t instr) {
  cpu->registers[R7] = cpu->registers[RPC];
  if((instr >> 11) & 0x1)
    cpu->registers[RPC] += sign_extend(instr & 0x7FF, 11);
  else
    cpu->registers[RPC] = cpu->registers[((instr >> 6) & 0x7)];
}

void ld(cpu_t *cpu, uint16_t instr) {
  uint16_t addr = cpu->registers[RPC] + sign_extend(instr & 0x1FF, 9);
  uint16_t dr = (instr >> 9) & 0x7;
  cpu->registers[dr] = cpu->memory[addr];
  update_flags(cpu->registers, dr);
}

void ldi(cpu_t *cpu, uint16_t instr){
  uint16_t addr = cpu->registers[RPC] + sign_extend(instr & 0x1FF, 9);
  uint16_t dr = (instr >> 9) & 0x7;
  cpu->registers[dr] = cpu->memory[cpu->memory[addr]];
  update_flags(cpu->registers, dr);
}

void ldr(cpu_t *cpu, uint16_t instr) {
  uint16_t br = (instr >> 6) & 0x7;
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t offset = sign_extend(instr & 0x3f, 6);

  cpu->registers[dr] = cpu->memory[cpu->registers[br] + offset];
  update_flags(cpu->registers, dr);
}

void lea(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t offset = sign_extend(instr & 0x1ff, 9);
  cpu->registers[dr] = cpu->registers[RPC] + offset;

  update_flags(cpu->registers, dr);
}

void not(cpu_t *cpu, uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;
  uint16_t sr = (instr >> 6) & 0x7;

  cpu->registers[dr] = ~cpu->registers[sr];
  update_flags(cpu->registers, dr);
}

void rti() {
  abort();
}

void res() {
  abort();
}

void st(cpu_t *cpu, uint16_t instr) {
  uint16_t sr = (instr >> 9) & 0x7;
  uint16_t offset = sign_extend(instr & 0x1ff, 9);

  cpu->memory[cpu->registers[RPC]+offset] = cpu->registers[sr];  
}

void sti(cpu_t *cpu, uint16_t instr) {
  uint16_t sr = (instr >> 9) & 0x7;
  uint16_t offset = sign_extend(instr & 0x1ff, 9);

  cpu->memory[cpu->memory[cpu->registers[RPC]+offset]] = cpu->registers[sr];
}

void str(cpu_t *cpu, uint16_t instr) {
  uint16_t sr = (instr >> 9) & 0x7;
  uint16_t br = (instr >> 6) & 0x7;
  uint16_t offset = sign_extend(instr & 0x3f, 6);
  cpu->memory[cpu->registers[br]+offset] = cpu->registers[sr];
}


void trap(cpu_t *cpu, uint16_t instr) {
  cpu->registers[R7] = cpu->registers[RPC];
  uint16_t trapvector8 = instr && 0xFF;
  trap_routine(cpu, trapvector8);  
}
