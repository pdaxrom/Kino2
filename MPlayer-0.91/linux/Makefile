
include ../config.mak

LIBNAME = libosdep.a

SRCS=getch2.c shmem.c strsep.c vsscanf.c scandir.c # timer.c

ifeq ($(TARGET_ARCH_X86),yes)
ifeq ($(TARGET_OS),Linux)
SRCS += lrmi.c vbelib.c
endif
endif

ifeq ($(MACOSX),yes)
SRCS += timer-macosx.c
else
SRCS += timer-lx.c
endif

OBJS=$(SRCS:.c=.o)

CFLAGS  = $(OPTFLAGS) -I. -I.. $(EXTRA_INC)
# -I/usr/X11R6/include/

.SUFFIXES: .c .o

# .PHONY: all clean

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBNAME):     $(OBJS)
	$(AR) r $(LIBNAME) $(OBJS)

all:    $(LIBNAME)

clean:
	rm -f *.o *.a *~

distclean:
	rm -f Makefile.bak *.o *.a *~ .depend

dep:    depend

depend:
	$(CC) -MM $(CFLAGS) $(SRCS) 1>.depend

#
# include dependency files if they exist
#
ifneq ($(wildcard .depend),)
include .depend
endif
