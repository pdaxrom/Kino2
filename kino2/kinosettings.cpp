#include <qmessagebox.h>
#include <qstringlist.h>
#include <qfile.h>
#include <qcstring.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>

#include <qcheckbox.h>
#include <qradiobutton.h>

#include "kinosettings.h"

KinoSettings::KinoSettings( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : KinoSettingsBase( parent, name, modal, fl )
{
    setCaption( tr(name ) );
    showMaximized();
}

KinoSettings::~KinoSettings() 
{
}

void KinoSettings::setSettings(KinoPrefs p)
{
    f_dropframes->setChecked(p.f_dropframes);
    f_directrendering->setChecked(p.f_directrendering);
    s_cache->setText(QString::number(p.s_cache));
    s_bandwidth->setText(QString::number(p.s_bandwidth));
    f_s_overlay->setChecked(p.f_s_overlay);
    f_s_doublebuffer->setChecked(p.f_s_doublebuffer);
    f_f_overlay->setChecked(p.f_f_overlay);
    f_f_doublebuffer->setChecked(p.f_f_doublebuffer);
    f_f_qvga->setChecked(p.f_f_qvga);
    b_mad->setChecked(p.f_mad);
    b_ffmpeg->setChecked(p.f_ffmpeg);
    b_another->setChecked(p.f_another);
    s_another->setText(p.s_another);
}

KinoPrefs KinoSettings::getSettings(void)
{
    KinoPrefs p;
    p.f_dropframes = f_dropframes->isChecked();
    p.f_directrendering = f_directrendering->isChecked();
    p.s_cache = s_cache->text().toInt(0, 10);
    p.s_bandwidth = s_bandwidth->text().toInt(0, 10);
    p.f_s_overlay = f_s_overlay->isChecked();
    p.f_s_doublebuffer = f_s_doublebuffer->isChecked();
    p.f_f_overlay = f_f_overlay->isChecked();
    p.f_f_doublebuffer = f_f_doublebuffer->isChecked();
    p.f_f_qvga = f_f_qvga->isChecked();
    p.f_mad = b_mad->isChecked();
    p.f_ffmpeg = b_ffmpeg->isChecked();
    p.f_another = b_another->isChecked();
    p.s_another = s_another->text();
    
    return p;
}
