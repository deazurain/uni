KERNELsrc = /usr/src/linux-headers-2.6.38-8-generic


obj-m += writetofile.o 

all:
	${MAKE} -C ${KERNELsrc} M=$(PWD) modules

clean:
	${MAKE} -C ${KERNELsrc} M=$(PWD) clean
