#include <qwidget.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include <qwidget.h>

#include <unistd.h>

#include "sldirectpainter.h"
#include "control.h"

Control::Control(QWidget *parent, const char *name, WFlags f) :
    QWidget(parent, name, f)
{
    sdp = NULL;
//    int size = QMAX( qApp->desktop()->width(), qApp->desktop()->height() );
//    currentFrame = new QImage( size, size, (QPixmap::defaultDepth() == 16) ? 16 : 32 );
//    rotatedFrame = new QImage( size, size, (QPixmap::defaultDepth() == 16) ? 16 : 32 );
    setBackgroundColor(QColor(0, 0, 0));
}

Control::~Control()
{
    if (sdp) delete sdp;
}

void Control::showScreen(bool mode)
{
    if (mode) {
	sdp = new SlDirectPainter(0x48, false, 0x1);
	if (!sdp->begin()) {
	    qDebug("failed to begin sldirectpainter.\n");
	} else {
	    qDebug("sldirectpainter ok.\n");
	}
	usleep(250000);
    }
}

void Control::hideScreen(void)
{
    sdp = NULL;
    delete sdp;
}

/*
void Control::keyPressEvent(QKeyEvent *event)
{
//    if (!isPlaying) return;
    qDebug("KeyEvent");
    switch (event->key()) {
	case Key_Space:
	    emit keyCommand("pause\n");
	    break;
	case Key_Right:
	    emit keyCommand("seek +1\n");
	    break;
	case Key_Left:
	    emit keyCommand("seek -1\n");
	    break;
	case Key_Up:
	    emit keyCommand("seek +10\n");
	    break;
	case Key_Down:
	    emit keyCommand("seek -10\n");
	    break;
	case Key_Escape:
	    emit keyCommand("quit\n");
	    break;
	default:
	    emit keyCommand("pause\n");
	    break;
    }
}
 */
