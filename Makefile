IDIR =.
CC=gcc
CFLAGS=-I$(IDIR)

_DEPS = mem.h regs.h instr.h helper.h cpu.h trap.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = lc3vm.o mem.o regs.o instr.o helper.o cpu.o trap.o

lc3vm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ lc3vm $(INCDIR)/*~ 
