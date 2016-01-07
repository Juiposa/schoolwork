PILOTHOME = /work/wgardner/pilot

CC = mpicc
CPPFLAGS += -I$(PILOTHOME)/include
CFLAGS = -g -O2
LDFLAGS += -L$(PILOTHOME)/lib -lpilot

all:
	$(CC) src/pal.c $(CFLAGS) -Iinclude $(LDFLAGS) -o pal
