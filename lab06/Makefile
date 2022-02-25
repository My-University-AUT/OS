CC      = gcc
CFLAGS  = -g
RM      = rm -f
TH      = -pthread

default: all

all: reader_writer philosopher

reader_writer: reader_writer.c
	$(CC) $(CFLAGS) $(TH) -o reader_writer reader_writer.c

philosopher: philosopher.c
	$(CC) $(CFLAGS) $(TH) -o philosopher philosopher.c


clean veryclean:
	$(RM) reader_writer philosopher