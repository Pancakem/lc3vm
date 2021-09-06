#include "cpu.h"
#include "mem.h"
#include "regs.h"

void init_cpu(cpu_t *cpu) {
  zero_memory(cpu->memory);
  zero_regs(cpu->registers);

  // set program start
  cpu->registers[RPC] = 0x3000;  
  cpu->running = 1;
}
