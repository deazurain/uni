CC=arm-unknown-linux-gnu-gcc
CFLAGS = -O2 -Wall -W

OUTPUT = hello

CFILES = hello.c user_gpio.c tank_user.c
OFILES = $(CFILES:.c=.o)

all: $(OFILES)
	$(CC) $(OFILES) -o $(OUTPUT)

%.o: %.c
	$(CC) -c $(CFLAGS) $< 

clean:
	rm -f *.o *% $(OUTPUT)
