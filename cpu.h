#include <stdint.h>

struct CPU {
  uint16_t memory[UINT16_MAX];
  uint16_t registers[10];
  int running;
};

typedef struct CPU cpu_t;

void init_cpu(cpu_t *cpu);
