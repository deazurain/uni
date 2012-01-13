CC=arm-unknown-linux-gnu-gcc
CFLAGS = -O2 -Wall -W

OUTPUT = tank

CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

all: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(OUTPUT)

%.o: %.c
	$(CC) -c $(CFLAGS) $< 

clean:
	rm -f *.o *% $(OUTPUT)
