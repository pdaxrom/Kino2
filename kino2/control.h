#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <qwidget.h>
#include <qtimer.h>

#include "sldirectpainter.h"

class Control : public QWidget
{
    Q_OBJECT

public:
    Control(QWidget *parent, const char *name = 0, WFlags f = 0);
    ~Control();
    void showScreen(bool mode);
    void hideScreen(void);

//protected:
//    void keyPressEvent(QKeyEvent *event);

//signals:
//    void keyCommand(QString str);

private:
    SlDirectPainter *sdp;
};

#endif
