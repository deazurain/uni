KERNELsrc = /usr/src/linux-headers-2.6.38-8-generic


obj-m += timer_module.o 

all:
	${MAKE} -C ${KERNELsrc} M=$(PWD) modules

clean:
	${MAKE} -C ${KERNELsrc} M=$(PWD) clean
