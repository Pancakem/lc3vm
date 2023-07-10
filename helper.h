#ifndef _HELPER_H_
#define _HELPER_H_

#include <stdint.h>
#include <sys/mman.h>
#include <sys/termios.h>

struct termios original_tio;

uint16_t read_data(uint16_t *data, int pos);
void write_data(uint16_t *data, int pos, uint16_t val);
void zero_data_region(uint16_t *data, int upto);
uint16_t check_key();
void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);
uint16_t bswap16(uint16_t x);
uint16_t sign_extend(uint16_t x, int bit_count);

#endif
