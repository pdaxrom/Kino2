TEMPLATE	= app
#CONFIG		= qt warn_on debug
CONFIG		= qt warn_on release
HEADERS		= player.h control.h ptyprocess.h misc.h kinosettings.h
SOURCES		= main.cpp player.cpp control.cpp ptyprocess.cpp misc.cpp kinosettings.cpp
LIBS            += -lqpe -lqte -ljpeg -lsl -lzdtm -lutil -s
TARGET		= dist/opt/QtPalmtop/bin/kino2
INTERFACES	= playerbase.ui kinosettingsbase.ui mediainfobase.ui
TRANSLATIONS	= kino2-ru.ts
