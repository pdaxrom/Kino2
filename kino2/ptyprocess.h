/****************************************************************************************
 * (c) Cacko Team,2002,2003								*
 * Kino2 video player									*
 * http://www.cacko.biz									*
 ****************************************************************************************/

#ifndef _PTYPROCESS_H_
#define _PTYPROCESS_H_

#include <qsocketnotifier.h>
#include <qglobal.h>
#include <qobject.h>
#include <qstrlist.h>


class PtyProcess : public QObject
{
Q_OBJECT
  public:
    PtyProcess();
    ~PtyProcess();
    int run(const char *cmd, char *const *args);
    void send_bytes(const char* s, int len);
    void send_string(const char* s);
    const char* deviceName();
  public slots:
    void error();
  signals:
    void done(int status);
    void block_in(const char* s, int len);
  protected slots:
    void readPty();
    void donePty();
  private:
    char ptynam[16];
    char ttynam[16];
    int fd;
    int cpid;
    int openPty();
    QSocketNotifier* sn_r;
    QSocketNotifier* sn_e;
};

#endif
