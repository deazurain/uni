KERNELsrc = /usr/src/linux-source-2.6.18-lart/

CFLAGS += -Werror

CROSS_COMPILE = arm-unknown-linux-gnu-
ARCH = arm

export CROSS_COMPILE
export ARCH

obj-m += lart_module.o 

all:
	${MAKE} -C ${KERNELsrc} M=$(PWD) modules

clean:
	${MAKE} -C ${KERNELsrc} M=$(PWD) clean
