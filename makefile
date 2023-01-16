
ifdef ARM_LINUX

TOOLS_PREFIX=arm-linux-gnueabi-
LIBDIRS = -L/home/ezequiel/work/beagleboneblack/rootfs/usr/lib
INCDIRS = -I/home/ezequiel/work/beagleboneblack/rootfs/usr/include \
			-I../../../common
INSTALL_DIR=/home/ezequiel/work/beagleboneblack/rootfs/apps

else

#	nativo
TOOLS_PREFIX=
LIBDIRS = -L/usr/local/ssl/lib
INCDIRS = -I/usr/local/ssl/include \
			-I../../../common 

endif

GCC = $(TOOLS_PREFIX)gcc
LD  = $(TOOLS_PREFIX)gcc
AS  = $(TOOLS_PREFIX)as
OBJCOPY = $(TOOLS_PREFIX)objcopy

all: ifname

%.o: %.c
	$(GCC) -g -Wall $(INCDIRS) -c $< -o $@

VPATH 	= ../

ifname: ifname.o
	$(LD) ifname.o -o $@ $(LIBDIRS) -ldl

clean:
	rm -f ifname *.o *~ *.bak *.i *.lst *.s

install: ifname
	cp ifname $(INSTALL_DIR)
