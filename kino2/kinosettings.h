#ifndef _KINOSETTINGS_H_
#define _KINOSETTINGS_H_

#include <qvariant.h>
#include <qdialog.h>
#include <qcstring.h>
#include <qstringlist.h>
#include <qlineedit.h>
#include <qwhatsthis.h>

#include "kinosettingsbase.h"

class KinoPrefs {
public:
    // Player
    bool	f_dropframes;
    bool	f_directrendering;
    // Media Stream
    int		s_cache;
    int		s_bandwidth;
    //Screen
    bool	f_s_overlay;
    bool	f_s_doublebuffer;
    //Fullscreen
    bool	f_f_overlay;
    bool	f_f_doublebuffer;
    bool	f_f_qvga;
    //Audio Decoder
    bool	f_mad;
    bool	f_ffmpeg;
    bool	f_another;
    QString	s_another;
};

class KinoSettings : public KinoSettingsBase
{ 
    Q_OBJECT

public:
    KinoSettings( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~KinoSettings();

    void setSettings(KinoPrefs p);
    KinoPrefs getSettings(void);
};

#endif
