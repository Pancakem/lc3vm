#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#include "helper.h"
#include "instr.h"
#include "mem.h"
#include "regs.h"
#include <stdlib.h>
#include <string.h>

extern int errno;

FILE *read_bin_file(const char *source) {
  FILE *f = fopen(source, "rb");
  return f;
}

bool read_program_into_memory(const char *source, uint16_t *memory) {
  FILE *f = read_bin_file(source);
  if (!f) {
    return false;
  }

  uint16_t origin;
  fread(&origin, sizeof(origin), 1, f);
  origin = bswap16(origin);
  uint16_t *read_start = memory + origin;
  int read = fread(read_start, sizeof(uint16_t), UINT16_MAX - origin, f);

  fclose(f);
  while (read-- > 0) {
    *read_start = bswap16(*read_start);
    ++read_start;
  }
  return true;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Please give me a program to run.\n");
    return -1;
  }

  uint16_t *mem = (uint16_t *)malloc(sizeof(uint16_t) * (1 << 16));

  if (!read_program_into_memory(argv[1], mem)) {
    puts("Could not open given program.");
    return -1;
  }

  signal(SIGINT, handle_interrupt);
  disable_input_buffering();

  // initialize cpu
  cpu_t *cpu = (cpu_t *)malloc(sizeof(cpu_t));
  init_cpu(cpu);

  memcpy(cpu->memory, mem, 1 << 16);
  free(mem);

  while (cpu->running) {
    uint16_t instruction = read_memory(cpu->memory, cpu->registers[RPC]++);
    uint16_t opcode = decode_instruction(instruction);
    // printf("\nRPC: %x\n", cpu->registers[RPC]);

    switch (opcode) {
    case BR:
      br(cpu, instruction);
      break;
    case ADD:
      add(cpu, instruction);
      break;
    case LD:
      ld(cpu, instruction);
      break;
    case JSR:
      jsr(cpu, instruction);
      break;
    case ST:
      st(cpu, instruction);
      break;
    case AND:
      and(cpu, instruction);
      break;
    case LDR:
      ldr(cpu, instruction);
      break;
    case STR:
      str(cpu, instruction);
      break;
    case RTI:
      rti();
      break;
    case NOT:
      not(cpu, instruction);
      break;
    case LDI:
      ldi(cpu, instruction);
      break;
    case STI:
      sti(cpu, instruction);
      break;
    case JMP:
      jmp(cpu, instruction);
      break;
    case RES:
      res();
      break;
    case LEA:
      lea(cpu, instruction);
      break;
    case TRAP:
      trap(cpu, instruction);
      break;

    // DEBUG
    default:
      printf("Unknown instruction: %d", opcode);
      cpu->running = 0;
      break;
    }
  }
  restore_input_buffering();
  free(cpu);
}
