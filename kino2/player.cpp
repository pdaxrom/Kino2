/****************************************************************************************
 * (c) Cacko Team,2002,2003								*
 * Kino2 video player									*
 * http://www.cacko.biz									*
 ****************************************************************************************/

#include <qpe/qpemenubar.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qtimer.h>
#include <qdir.h>
#include <qlcdnumber.h>
#include <qslider.h>
#include <qgfx_qws.h>
#include <sl/slfileselector.h>
#include <qpe/config.h>
#include <sl/slmisc.h>

#include "player.h"
#include "ptyprocess.h"
#include "control.h"
#include "misc.h"
#include "kinosettings.h"
#include "mediainfobase.h"

#define KINO_VERSION	"0.2 beta"

Player::Player( QWidget* parent,  const char* name, WFlags fl )
    : QMainWindow( parent, name, fl ), isPlaying(false), isPausing(false), isIdentify(false), selectedFile("")
{
    setCaption(tr("Kino 2"));
    m_fileMenu = new QPopupMenu(0, "file_menu");
    connect(m_fileMenu, SIGNAL(activated(int)), this, SLOT(fileMenu(int)));
    m_fileMenu->insertItem(tr("Open..."), 0);
    m_fileMenu->insertItem(tr("Open URL..."), 1);
    m_fileMenu->insertSeparator(2);
    m_fileMenu->insertItem(tr("File info..."), 3);
    m_fileMenu->insertSeparator(4);
    m_fileMenu->insertItem(tr("Preferences..."), 5);

    m_viewMenu = new QPopupMenu(0, "view_menu");
    m_viewMenu->setCheckable(true);
    connect(m_viewMenu, SIGNAL(activated(int)), this, SLOT(viewMenu(int)));
    m_viewMenu->insertItem(tr("Scale"), 0);
    m_viewMenu->insertItem(tr("Fullscreen"), 1);

    loadSettings();

    m_helpMenu = new QPopupMenu(0, "help");
    connect(m_helpMenu, SIGNAL(activated(int)), this, SLOT(helpMenu(int)));
    m_helpMenu->insertItem(tr("About"), 0);

    menu = new QPEMenuBar(this);
    menu->insertItem(tr("File"), m_fileMenu);
    menu->insertItem(tr("View"), m_viewMenu);
    menu->insertItem(tr("Help"), m_helpMenu);

    stack = new QWidgetStack( this );
    stack->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ) );
    setCentralWidget( stack );

    contents = new PlayerBase( stack );
    stack->addWidget( contents, 0 );
    stack->raiseWidget( contents );

    connect( contents->play_button, SIGNAL( clicked() ),
	     this, SLOT( playClicked() ) );
    connect( contents->pause_button, SIGNAL( clicked() ),
	     this, SLOT( pauseClicked() ) );
    connect( contents->stop_button, SIGNAL( clicked() ),
	     this, SLOT( stopClicked() ) );
    connect( contents->eject_button, SIGNAL( clicked() ),
	     this, SLOT( ejectClicked() ) );
    connect( contents->rev_button, SIGNAL( clicked() ),
	     this, SLOT( revClicked() ) );
    connect( contents->fwd_button, SIGNAL( clicked() ),
	     this, SLOT( fwdClicked() ) );

    slf = new SlFileSelector("", "", stack, "");
    connect(slf, SIGNAL(fileSelected(const QFileInfo &)), this, SLOT(fileSelected(const QFileInfo &)));
    slf->setListView();
    
    process = new PtyProcess();
    connect( process, SIGNAL(done(int)), this, SLOT(done(int)));
    connect( process, SIGNAL(block_in(const char*, int)), this, SLOT(block_in(const char*, int)));
    
    minfo = NULL;
}

Player::~Player()
{
    saveSettings();
    delete process;
}

void Player::loadSettings()
{
    Config cfg("kino2");
    cfg.setGroup("View");
    useScale = cfg.readBoolEntry("Scale");
    m_viewMenu->setItemChecked(0, useScale);
    useFullscreen = cfg.readBoolEntry("Fullscreen");
    m_viewMenu->setItemChecked(1, useFullscreen);

    cfg.setGroup("Player");
    kinoPrefs.f_dropframes = cfg.readBoolEntry("framedrop", true);
    kinoPrefs.f_directrendering = cfg.readBoolEntry("directrendering", true);

    cfg.setGroup("Media Stream");
    kinoPrefs.s_cache = cfg.readNumEntry("cache",0);
    kinoPrefs.s_bandwidth = cfg.readNumEntry("bandwidth",0);

    cfg.setGroup("Screen");
    kinoPrefs.f_s_overlay = cfg.readBoolEntry("overlay", true);
    kinoPrefs.f_s_doublebuffer = cfg.readBoolEntry("doublebuffer");

    cfg.setGroup("Fullscreen");
    kinoPrefs.f_f_overlay = cfg.readBoolEntry("overlay", true);
    kinoPrefs.f_f_doublebuffer = cfg.readBoolEntry("doublebuffer");
    kinoPrefs.f_f_qvga = cfg.readBoolEntry("qvga", true);

    cfg.setGroup("Audio decoder");
    kinoPrefs.f_mad = cfg.readBoolEntry("MAD", true);
    kinoPrefs.f_ffmpeg = cfg.readBoolEntry("ffmpeg");
    kinoPrefs.f_another = cfg.readBoolEntry("another");
    kinoPrefs.s_another = cfg.readEntry("anothername");
}

void Player::saveSettings()
{
    Config cfg("kino2");
    cfg.setGroup("View");
    cfg.writeEntry("Scale", useScale);
    cfg.writeEntry("Fullscreen", useFullscreen);
    
    cfg.setGroup("Player");
    cfg.writeEntry("framedrop", kinoPrefs.f_dropframes);
    cfg.writeEntry("directrendering", kinoPrefs.f_directrendering);

    cfg.setGroup("Media Stream");
    cfg.writeEntry("cache", kinoPrefs.s_cache);
    cfg.writeEntry("bandwidth", kinoPrefs.s_bandwidth);

    cfg.setGroup("Screen");
    cfg.writeEntry("overlay", kinoPrefs.f_s_overlay);
    cfg.writeEntry("doublebuffer", kinoPrefs.f_s_doublebuffer);

    cfg.setGroup("Fullscreen");
    cfg.writeEntry("overlay", kinoPrefs.f_f_overlay);
    cfg.writeEntry("doublebuffer", kinoPrefs.f_f_doublebuffer);
    cfg.writeEntry("qvga", kinoPrefs.f_f_qvga);

    cfg.setGroup("Audio decoder");
    cfg.writeEntry("MAD", kinoPrefs.f_mad);
    cfg.writeEntry("ffmpeg", kinoPrefs.f_ffmpeg);
    cfg.writeEntry("another", kinoPrefs.f_another);
    cfg.writeEntry("anothername", kinoPrefs.s_another);    
}

void Player::fileSelected(const QFileInfo &fs)
{
    selectedFile = fs.filePath();
    stack->raiseWidget(contents);
    setCaption(fs.fileName() + tr(" - Kino 2"));
}

void Player::done(int status)
{
    if (isIdentify) {
	isIdentify = false;
	MediaInfoBase mdf(this, tr("File info"), TRUE, 0);
	mdf.title_label->setText(minfo->Title);
	mdf.album_label->setText(minfo->Album);
	mdf.artist_label->setText(minfo->Artist);
	mdf.year_label->setText(minfo->Year);
	
	mdf.width_label->setText(QString::number(minfo->VIDEO_WIDTH));
	mdf.height_label->setText(QString::number(minfo->VIDEO_HEIGHT));
	mdf.vformat_label->setText(minfo->VIDEO_FORMAT);
	mdf.fps_label->setText(QString::number(minfo->VIDEO_FPS));

	mdf.achans_label->setText(QString::number(minfo->AUDIO_NCH));
	mdf.acodec_label->setText(minfo->AUDIO_CODEC);
	mdf.arate_label->setText(QString::number(minfo->AUDIO_RATE));
	mdf.abitrate_label->setText(QString::number(minfo->AUDIO_BITRATE));
	
	mdf.exec();
	return;
    }
    if (useFullscreen && isPlaying) {
	delete fscr_control;
	showNormal();
	contents->show();
	menu->show();
	stack->raiseWidget(contents);
//	SlMisc::enableAutoPowerOff(true, true, true);
    }
    if (isPausing) isPausing = false;
    if (isPlaying) isPlaying = false;
//    qDebug("done()...");
}

void Player::block_in(const char* s, int len)
{
    if (isIdentify) {
      char str[128];
    
      int i = 0;
      int j;
    
      while (i < len) {
    
	j = 0;
	while ((s[i] != 0) && (s[i] != '\n')) {
	    str[j++] = s[i++];
	}
	i++;
	str[j] = 0;

	if (strncmp(str, " Title:", 7) == 0) {
	    minfo->Title = QString(&str[8]);
	    setCaption(minfo->Title + tr(" - Kino 2"));
	} else if (strncmp(str, " Artist:", 8) == 0) {
	    minfo->Artist = QString(&str[9]);
	} else if (strncmp(str, " Album:", 7) == 0) {
	    minfo->Album = QString(&str[8]);
        } else if (strncmp(str, " Year:", 6) == 0) {
	    minfo->Year = QString(&str[7]);
	} else if (strncmp(str, " Comment:", 9) == 0) {
	    minfo->Comment = QString(&str[10]);
	} else if (strncmp(str, " Track:", 7) == 0) {
	    minfo->Track = QString(&str[8]);
	} else if (strncmp(str, " Genre:", 7) == 0) {
	    minfo->Genre = QString(&str[8]);
	} else if (strncmp(str, "ID_FILENAME=", 12) == 0) {
	    minfo->FILENAME = QString(&str[12]);
	} else if (strncmp(str, "ID_AUDIO_CODEC=", 15) == 0) {
	    minfo->AUDIO_CODEC = QString(&str[15]);
	} else if (strncmp(str, "ID_AUDIO_FORMAT=", 16) == 0) {
	    minfo->AUDIO_FORMAT = QString(&str[16]).toInt();
	} else if (strncmp(str, "ID_AUDIO_BITRATE=", 17) == 0) {
	    minfo->AUDIO_BITRATE = QString(&str[17]).toInt();
	} else if (strncmp(str, "ID_AUDIO_RATE=", 14) == 0) {
	    minfo->AUDIO_RATE = QString(&str[14]).toInt();
	} else if (strncmp(str, "ID_AUDIO_NCH=", 13) == 0) {
	    minfo->AUDIO_NCH = QString(&str[13]).toInt();
	} else if (strncmp(str, "ID_LENGTH=", 10) == 0) {
	    minfo->LENGTH = QString(&str[10]).toInt();
	} else if (strncmp(str, "ID_VIDEO_FORMAT=", 16) == 0) {
	    minfo->VIDEO_FORMAT = QString(&str[16]);
	} else if (strncmp(str, "ID_VIDEO_BITRATE=", 17) == 0) {
	    minfo->VIDEO_BITRATE = QString(&str[17]).toInt();
	} else if (strncmp(str, "ID_VIDEO_WIDTH=", 15) == 0) {
	    minfo->VIDEO_WIDTH = QString(&str[15]).toInt();
	} else if (strncmp(str, "ID_VIDEO_HEIGHT=", 16) == 0) {
	    minfo->VIDEO_HEIGHT = QString(&str[16]).toInt();
	} else if (strncmp(str, "ID_VIDEO_FPS=", 13) == 0) {
	    minfo->VIDEO_FPS = QString(&str[13]).toFloat();
	} else if (strncmp(str, "ID_VIDEO_ASPECT=", 16) == 0) {
	    minfo->VIDEO_ASPECT = QString(&str[16]).toInt();
	}
    
      }
    } else {
//	qDebug(">>" + QString(s));
    }
}

void Player::identifyFile()
{
    const char *args[40];
    int i = 0;
    args[i++] = "/usr/local/bin/mplayer";
    args[i++] = "-identify";
    args[i++] = selectedFile.ascii();
    args[i++] = NULL;

    if (minfo) delete minfo;
    minfo = new MediaInfo();
    
    isIdentify = true;

    process->run(args[0], (char *const *)args);
}

void Player::playClicked()
{
    if (isPausing && isPlaying) {
	isPausing = false;
	process->send_string("pause\n");
	return;
    }
    if ((isPlaying == false) && (selectedFile != "") && !isIdentify) {
	const char *args[40];
	char buf_geom[64];
	QString vop_args;
	QString s_cache;
	QString s_band;
	int i = 0;

//	SlMisc::enableAutoPowerOff(false, false, false);

	args[i++] = "/usr/local/bin/mplayer";
	args[i++] = "-slave";
	args[i++] = "-really-quiet";
	if (kinoPrefs.f_directrendering)
	    args[i++] = "-dr";
	if (kinoPrefs.f_dropframes)
	    args[i++] = "-framedrop";
	args[i++] = "-ac";
	if (kinoPrefs.f_ffmpeg)
	    args[i++] = "ffmp2";
	else
	    args[i++] = "mad";

	total_time = 0;
	QPoint as = contents->screen->mapToGlobal(QPoint (0,0));
	int orient = qt_screen->transformOrientation();
	qDebug("Or = " + QString::number(orient));
	if (useFullscreen) {
	    args[i++] = "-vo";
	    if (kinoPrefs.f_f_overlay)
		args[i++] = "fbdev:vidix";
	    else
		args[i++] = "fbdev";

	    if (kinoPrefs.f_f_doublebuffer)
		args[i++] = "-double";

	    fscr_control = new Control(this);
	    menu->hide();
	    contents->hide();
	    fscr_control->showScreen(kinoPrefs.f_f_qvga);
	    showFullScreen();

	    if (kinoPrefs.f_f_qvga) {
		if (kinoPrefs.f_f_overlay) {
		    args[i++] = "-vop";
		    args[i++] = "rotate=1";
		    args[i++] = "-geometry";
		    args[i++] = "0:0";
		} else {
		    args[i++] = "-geometry";
		    args[i++] = "50%:50%";
		    args[i++] = "-vop";
		    args[i++] = "flip=yes,mirror=yes";
		}
	    } else {
		fscr_control->setFixedSize(qt_screen->width(), qt_screen->height());
		fscr_control->show();
		if (orient == 3) {
		    args[i++] = "-vop";
		    if (useScale) {
			vop_args = "rotate=1,scale=-2:" + QString::number(qt_screen->height());
			args[i++] = vop_args.ascii();
		    } else {
			args[i++] = "rotate=1";
		    }
		} else {
		    if (useScale) {
			args[i++] = "-vop";
			vop_args = "scale=" + QString::number(qt_screen->width()) + ":-2";
			args[i++] = vop_args.ascii();
		    }
		}
		args[i++] = "-geometry";
		args[i++] = "50%:50%";
	    }
	} else {
	    args[i++] = "-vo";
	    if (kinoPrefs.f_s_overlay)
		args[i++] = "fbdev:vidix";
	    else
		args[i++] = "fbdev";
		
	    if (kinoPrefs.f_s_doublebuffer)
		args[i++] = "-double";

	    int x, y, w, h;
	    if (orient == 3) {
		x = as.y();
		y = as.x();
		w = contents->screen->height();
		h = contents->screen->width();
		x += (w / 2);
		y += (h / 2);
		sprintf(buf_geom, "%d%%"":""%d%%",  100 - (x * 100) / qt_screen->height(),
						(y * 100) / qt_screen->width());
		args[i++] = "-geometry";
	        args[i++] = buf_geom;
		args[i++] = "-vop";
		    if (useScale) {
			vop_args = "rotate=1,scale=-2:" + QString::number(contents->screen->height()-32);
			args[i++] = vop_args.ascii();
		    } else {
			args[i++] = "rotate=1";
		    }
	    } else {
		x = as.x();
		y = as.y();
		w = contents->screen->width();
		h = contents->screen->height();
		x += (w / 2);
		y += (h / 2);
		sprintf(buf_geom, "%d%%"":""%d%%",  (x*100)/qt_screen->width(),
						 (y*100)/qt_screen->height());
		args[i++] = "-geometry";
		args[i++] = buf_geom;
		if (useScale) {
		    args[i++] = "-vop";
		    vop_args = "scale=" + QString::number(qt_screen->width()) + ":-2";
		    args[i++] = vop_args.ascii();
		}
	    }
	    qDebug("x = " + QString::number(x));
	    qDebug("y = " + QString::number(y));
	    qDebug("w = " + QString::number(contents->screen->width()));
	    qDebug("h = " + QString::number(contents->screen->height()));
	}

	if (kinoPrefs.s_cache > 0) {
	    args[i++] = "-cache";
	    s_cache = QString::number(kinoPrefs.s_cache);
	    args[i++] = s_cache.ascii();
	}

	if (kinoPrefs.s_bandwidth > 0) {
	    args[i++] = "-bandwidth";
	    s_band = QString::number(kinoPrefs.s_bandwidth);
	    args[i++] = s_band.ascii();
	}

	if (useScale) {
	    args[i++] = "-sws";
	    args[i++] = "0";
	}

	args[i++] = selectedFile.ascii();
	args[i++] = NULL;

	process->run(args[0], (char *const *)args);
	isPlaying = true;
	isPausing = false;
    }
}

void Player::pauseClicked()
{
    if (isPlaying)
    {
	isPausing = true;
	process->send_string("pause\n");
    }
}

void Player::stopClicked()
{
    if (isPlaying)
	process->send_string("quit\n");
}

void Player::revClicked()
{
    if (isPlaying)
	process->send_string("seek -5\n");
}

void Player::fwdClicked()
{
    if (isPlaying)
	process->send_string("seek +5\n");
}

void Player::ejectClicked()
{
    if (isPlaying)
	process->send_string("quit\n");
    stack->raiseWidget(slf);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
	case Key_Space:
	    process->send_string("pause\n");
	    break;
	case Key_Right:
	    process->send_string("seek +1\n");
	    break;
	case Key_Left:
	    process->send_string("seek -1\n");
	    break;
	case Key_Up:
	    process->send_string("seek +10\n");
	    break;
	case Key_Down:
	    process->send_string("seek -10\n");
	    break;
	case Key_Escape:
	    process->send_string("quit\n");
	    break;
	default:
	    process->send_string("pause\n");
	    break;
    }
}

void Player::goodBye()
{
    close();
}

void Player::fileMenu(int item)
{
    if (item == 0) {
	if (isPlaying)
	    process->send_string("quit\n");
	stack->raiseWidget(slf);
    } else if (item == 1) {
	if (isPlaying)
	    process->send_string("quit\n");
	InputDialog *urlDlg;
	urlDlg = new InputDialog(this,tr("Open URL..."),TRUE, 0);
	urlDlg->exec();
	if( urlDlg->result() == 1 ) {
	    selectedFile = urlDlg->LineEdit1->text();
	    setCaption(selectedFile + tr(" - Kino 2"));
	}
	delete urlDlg;
    } else if (item == 3) {
	if (!isPlaying && !isIdentify) identifyFile();
    } else if (item == 5) {
	if (isPlaying)
	    process->send_string("quit\n");
	KinoSettings *kinoset = new KinoSettings(this, tr("Preferences..."),TRUE,0);
	kinoset->setSettings(kinoPrefs);
	if (kinoset->exec() == 1) {
	    kinoPrefs = kinoset->getSettings();
	    saveSettings();
	    loadSettings();
	}
    }
}

void Player::viewMenu(int item)
{
    if (item == 0) {
	m_viewMenu->setItemChecked(0, (useScale = useScale?false:true));
    } else if (item == 1) {
	m_viewMenu->setItemChecked(1, (useFullscreen = useFullscreen?false:true));
    }
}

void Player::helpMenu(int item)
{
    if (item == 0) {
	QString str = tr("Kino 2 v" KINO_VERSION " (SL-C7x0)\n"
		  "Mplayer Qtopia GUI\n"
		  "(c) Cacko Team, 2003\n"
		  "http://www.cacko.biz\n");
	QMessageBox::information(this, tr("Kino 2"), str);
    }
}
