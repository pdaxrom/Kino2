
LIB	= libgui.a

include ../config.mak
include config.mak

INCDIR  = -I. -I../loader -I./wm -I./skin $(FREETYPE_INC) $(GTKINC) $(EXTRA_INC) 

OPTIMIZE =  $(OPTFLAGS) \
            -fexpensive-optimizations -fschedule-insns2 -Wall
ifeq ($(TARGET_ARCH_X86),yes)
OPTIMIZE += -malign-double
endif

CFLAGS = $(OPTIMIZE) $(INCDIR) $(DEBUG) 

SRCS = wm/ws.c wm/wsxdnd.c app.c interface.c cfg.c bitmap.c \
	skin/skin.c skin/font.c skin/cut.c \
	mplayer/widgets.c mplayer/play.c mplayer/mw.c mplayer/sw.c mplayer/menu.c mplayer/pb.c mplayer/common.c \
	mplayer/gtk/menu.c mplayer/gtk/mb.c mplayer/gtk/about.c mplayer/gtk/pl.c mplayer/gtk/sb.c mplayer/gtk/fs.c mplayer/gtk/opts.c mplayer/gtk/url.c mplayer/gtk/eq.c mplayer/gtk/common.c
OBJS = $(SRCS:.c=.o)

.SUFFIXES: .c .o

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

### TARGETS ###

$(LIB):	.depend	$(OBJS)
	rm -f $(LIB)
	$(AR) rc $(LIB) $(OBJS) $(MPLAYEROBJS)

all:	$(LIB)

clean:
	rm -rf $(OBJS) *.o *~ *.bak main $(PRG) $(LIB) .depend

#dep:	depend
#
#depend:
#	makedepend -- $(CFLAGS) -- $(SRCS) &>/dev/null
#

distclean: clean

dep:    depend

depend: .depend

.depend: Makefile config.mak
	$(CC) -MM $(CFLAGS) $(SRCS) 1>.depend

#
# include dependency files if they exist
#
ifneq ($(wildcard .depend),)
include .depend
endif
