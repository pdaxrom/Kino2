/****************************************************************************************
 * (c) Cacko Team,2002,2003								*
 * Kino2 video player									*
 * http://www.cacko.biz									*
 ****************************************************************************************/

#ifndef _SLDIRECTPAINTER_H_
#define _SLDIRECTPAINTER_H_

#include <qobject.h>

class SlDirectPainter : public QObject 
{

    Q_OBJECT

public:
    SlDirectPainter(int, bool, int);
    ~SlDirectPainter();
    bool begin(void);
    bool end(void);
//    int width(void);
//    int height(void);
    void *frameBuffer(void);
private slots:
    void systemMessage(const QCString &msg,const QByteArray &data);
};

#endif
