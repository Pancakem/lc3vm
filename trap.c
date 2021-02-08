#include <stdio.h>
#include "trap.h"
#include "regs.h"

void trap_routine(cpu_t *cpu, uint16_t tv8) {
  uint16_t c;
  uint16_t *cp;
  switch(tv8) {
  case GETC:
    cpu->registers[R0] = (uint16_t)getchar();
    break;
  case OUT:
    putc((char)cpu->registers[R0], stdout);
    fflush(stdout);
    break;
  case PUTS:
    break;
  case IN:
    printf("Enter a character: ");
    c = getchar();
    putc((char)c, stdout);
    cpu->registers[R0] = c;
    break;
  case PUTSP:
    cp = cpu->memory + cpu->registers[R0];
    while (*cp)
    {
      char char1 = (*cp) & 0xFF;
      putc(char1, stdout);
      char char2 = (*cp) >> 8;
        if (char2) putc(char2, stdout);
        ++cp;
    }
    fflush(stdout);
    break;
  case HALT:
    puts("HALT");
    fflush(stdout);
    cpu->running = 0;
    break;
  }
  
}
