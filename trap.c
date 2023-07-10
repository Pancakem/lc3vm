#include "trap.h"
#include "regs.h"
#include <stdio.h>

void trap_routine(cpu_t *cpu, uint16_t tv8) {
  uint16_t c;
  uint16_t *cp;
  char char1, char2;
  switch (tv8) {
  case GETC:
    cpu->registers[R0] = (uint16_t)getchar();
    update_flags(cpu->registers, R0);
    break;
  case OUT:
    putc((char)cpu->registers[R0], stdout);
    fflush(stdout);
    break;
  case PUTS:
    cp = cpu->memory + cpu->registers[R0];
    while (*cp) {
      putc((char)*cp, stdout);
      ++cp;
    }
    fflush(stdout);
    break;
  case IN:
    printf("Enter a character: ");
    c = getchar();
    putc((char)c, stdout);
    cpu->registers[R0] = c;
    update_flags(cpu->registers, R0);
    break;
  case PUTSP:
    cp = cpu->memory + cpu->registers[R0];
    while (*cp) {
      char1 = (*cp) & 0xFF;
      putc(char1, stdout);
      char2 = (*cp) >> 8;
      if (char2)
        putc(char2, stdout);
      ++cp;
    }
    fflush(stdout);
    break;
  case HALT:
    fflush(stdout);
    cpu->running = 0;
    break;

  default:
    printf("Unknown trap opcode %d\n", tv8);
    break;
  }
}
