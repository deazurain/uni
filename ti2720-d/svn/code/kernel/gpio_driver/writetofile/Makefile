CC=arm-unknown-linux-gnu-gcc
CFLAGS = -O2 -Wall -W

OUTPUT = write

CFILES = writetofile.c
OFILES = $(CFILES:.c=.o)

all: $(OFILES)
	$(CC) $(OFILES) -o $(OUTPUT)

%.o: %.c
	$(CC) -c $(CFLAGS) $< 

clean:
	rm -f *.o *% $(OUTPUT)
