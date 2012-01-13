# unload module and remove filenode
rmmod pwm_module.ko
rm -f /dev/lart

# make filenode and load module
mknod /dev/lart c 121 0
insmod pwm_module.ko
