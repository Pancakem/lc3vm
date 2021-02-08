#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

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
