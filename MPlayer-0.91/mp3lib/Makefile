
include ../config.mak

SRCS = sr1.c
OBJS = sr1.o
# OBJS = $(SRCS:.c,.s=.o)
ifeq ($(TARGET_ARCH_SGI_MIPS),yes)
OPTFLAGS := $(OPTFLAGS:-O4=-O0)
endif
CFLAGS  = $(OPTFLAGS) $(EXTRA_INC)
ifeq ($(TARGET_ARCH_X86),yes)
SRCS += decode_i586.c
OBJS += decode_i586.o
SRCS += decode_MMX.c dct64_MMX.c tabinit_MMX.c
OBJS += decode_MMX.o dct64_MMX.o tabinit_MMX.o
#ifeq ($(TARGET_SSE),yes)
#SRCS += dct64_sse.s
#OBJS += dct64_sse.o
#endif
SRCS += dct36_3dnow.s dct64_3dnow.c
OBJS += dct36_3dnow.o dct64_3dnow.o
SRCS += dct36_k7.s dct64_k7.c
OBJS += dct36_k7.o dct64_k7.o
endif
ifeq ($(TARGET_ARCH_POWERPC),yes)
ifeq ($(TARGET_ALTIVEC),yes)
SRCS += dct64_altivec.c
OBJS += dct64_altivec.o
ifeq ($(TARGET_OS),Darwin)
CFLAGS += -faltivec
else
CFLAGS += -maltivec -mabi=altivec
endif
endif
endif

.SUFFIXES: .c .o

# .PHONY: all clean

all:	libMP3.a

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

decode_i586.o: decode_i586.c
	$(CC) -c $(CFLAGS) -fomit-frame-pointer -o $@ $<

.s.o:
	$(CC) -c $(CFLAGS) -o $@ $<

libMP3.a:	$(OBJS)
	$(AR) r libMP3.a $(OBJS)
ifeq ($(TARGET_OS),CYGWIN)
	./mp3lib_objfix.sh
endif
ifeq ($(TARGET_OS),OpenBSD)
	./mp3lib_objfix.sh
endif
test1:	libMP3.a test.c
	$(CC) $(CFLAGS) test.c ../libvo/aclib.c -o test1 -I.. ./libMP3.a ../mp_msg-mencoder.o ../cpudetect.o -lm

test2:	libMP3.a test2.c
	$(CC) $(CFLAGS) test2.c ../libvo/aclib.c -o test2 -I.. ./libMP3.a ../mp_msg-mencoder.o ../cpudetect.o -lm

clean:
	rm -f *~ *.o *.a

distclean:
	rm -f *~ *.o *.a Makefile.bak .depend

dep:    depend

depend:
	$(CC) -MM $(CFLAGS) $(SRCS) 1>.depend

#
# include dependency files if they exist
#
ifneq ($(wildcard .depend),)
include .depend
endif
