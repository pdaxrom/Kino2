/****************************************************************************************
 * (c) Cacko Team,2002,2003								*
 * Kino2 video player									*
 * http://www.cacko.biz									*
 ****************************************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <qpe/qpemenubar.h>
#include <qmainwindow.h>
#include <qlist.h>
#include <qmap.h>
#include <qvbox.h>
#include <qwidgetstack.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtimer.h>
#include <sl/slfileselector.h>
#include "playerbase.h"
#include "ptyprocess.h"
#include "control.h"
#include "kinosettings.h"

class MediaInfo {
public:
    MediaInfo() {
	VIDEO_BITRATE = 0;
	VIDEO_WIDTH = 0;
	VIDEO_HEIGHT = 0;
	VIDEO_FPS = 0;
	VIDEO_FORMAT = "";
	AUDIO_CODEC = "";
	AUDIO_FORMAT = 0;
	AUDIO_BITRATE = 0;
	AUDIO_RATE = 0;
	AUDIO_NCH = 0;
	LENGTH = 0;
    };
    ~MediaInfo() {};
    QString	Title;
    QString	Artist;
    QString	Album;
    QString	Year;
    QString	Comment;
    QString	Track;
    QString	Genre;
    
    QString	FILENAME;
    QString	AUDIO_CODEC;
    int		AUDIO_FORMAT;
    int		AUDIO_BITRATE;
    int		AUDIO_RATE;
    int		AUDIO_NCH;
    int		LENGTH;
    QString	VIDEO_FORMAT;
    int		VIDEO_BITRATE;
    int		VIDEO_WIDTH;
    int		VIDEO_HEIGHT;
    float	VIDEO_FPS;
    int		VIDEO_ASPECT;
};

class Player : public QMainWindow
{ 
    Q_OBJECT

public:
    Player( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Player();

private:
    Control	*fscr_control;
    SlFileSelector	*slf;
    QPEMenuBar	*menu;
    QPopupMenu	*m_fileMenu;
    QPopupMenu	*m_viewMenu;
    QPopupMenu	*m_helpMenu;
    QWidgetStack *stack;
    PlayerBase	*contents;
    bool	useScale;
    bool	useFullscreen;
    bool	isPlaying;
    bool	isPausing;
    bool	isIdentify;
    QString	selectedFile;
    int		total_time;
    PtyProcess	*process;
    QColor	old_bg_color;

    KinoPrefs	kinoPrefs;
    MediaInfo	*minfo;

    void loadSettings();
    void saveSettings();
    void identifyFile();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void fileMenu(int item);
    void viewMenu(int item);
    void helpMenu(int item);
    void playClicked(void);
    void pauseClicked(void);
    void ejectClicked(void);
    void stopClicked(void);
    void revClicked(void);
    void fwdClicked(void);
    void done(int status);
    void block_in(const char* s, int len);
    
protected slots:
    void goodBye();
    void fileSelected(const QFileInfo &fs);
};

#endif // _PLAYER_H_
