
LIBNAME = libmpeg2.a

include ../config.mak

SRCS	= header.c idct.c idct_mmx.c idct_mlib.c \
		motion_comp.c motion_comp_mmx.c motion_comp_mlib.c \
		slice.c stats.c # decode.c
OBJS	= $(SRCS:.c=.o)
OBJS	+= $(SRCS:.S=.o)
INCLUDE = -I. -I../libvo -I.. $(EXTRA_INC) $(MLIB_INC) -I../ipp/include
CFLAGS  = $(OPTFLAGS) $(INCLUDE) -DMPG12PLAY

ifeq ($(TARGET_ARCH_ARM),yes)
SRCS   += simple_idct_arm.S
CFLAGS += -DARCH_ARM -DUSE_IPP
endif

.SUFFIXES: .c .o
.SUFFIXES: .S .o

# .PHONY: all clean

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.S.o:
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBNAME):	$(OBJS)
	$(AR) r $(LIBNAME) $(OBJS)

all:	$(LIBNAME)

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
