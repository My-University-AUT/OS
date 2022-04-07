CC      = gcc
CFLAGS  = -g
RM      = rm -f
TH      = -pthread

default: all

all: serial parallel

serial: serial.c
	$(CC) $(CFLAGS) -o serial serial.c

parallel: parallel.c
	$(CC) $(CFLAGS) $(TH) -o parallel parallel.c -lm

clean veryclean:
	$(RM) serial parallel