#include "mem.h"
#include "helper.h"

void zero_memory(uint16_t *mem) {
  zero_data_region(mem, 1 << 16);
}

uint16_t read_memory(uint16_t *mem, int addr){
  if(addr == KBSR) {
    if(check_key()){
      write_memory(mem, KBSR, 1 << 15);
      write_memory(mem, KBDR, getchar());
    }else {
      write_memory(mem, KBSR, 0);
    }
  }
  return read_data(mem, addr);
}

void write_memory(uint16_t *mem, int addr, int val) {
  write_data(mem, addr, val);
}
