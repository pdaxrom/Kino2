/****************************************************************************************
 * (c) Cacko Team,2002,2003								*
 * Kino2 video player									*
 * http://www.cacko.biz									*
 ****************************************************************************************/

#include <qapplication.h>
#include <qsocketnotifier.h>
#include <qstring.h>

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include <pty.h>

#include "ptyprocess.h"


#undef VERBOSE_DEBUG

PtyProcess::PtyProcess()
{
    cpid = 0;
    fd = 0;
}

PtyProcess::~PtyProcess()
{
    donePty();
}

void PtyProcess::donePty()
{
    int status = 0;
    if (!fd) return;
    ::close(fd);
    if (cpid) {
	kill(cpid, SIGHUP);
	waitpid(cpid, &status, 0);
    }
    disconnect(sn_r, SIGNAL(activated(int)),this,SLOT(readPty()));
    disconnect(sn_e, SIGNAL(activated(int)),this,SLOT(error()));
    delete sn_r;
    delete sn_e;
    fd = 0;
    emit done(status);
}


const char* PtyProcess::deviceName()
{
    return ttynam;
}


void PtyProcess::error()
{
    donePty();
}

int PtyProcess::run(const char *cmd, char *const *args)
{
    int ttyfd;
    fd = openPty();

    sn_r = new QSocketNotifier(fd,QSocketNotifier::Read,this);
    sn_e = new QSocketNotifier(fd,QSocketNotifier::Exception,this);
    connect(sn_r,SIGNAL(activated(int)),this,SLOT(readPty()));
    connect(sn_e,SIGNAL(activated(int)),this,SLOT(error()));

    ttyfd = open(ttynam, O_RDWR);
    cpid = fork();
    if ( !cpid ) {
	for (int sig = 1; sig < NSIG; sig++) signal(sig,SIG_DFL);
	dup2(ttyfd, STDIN_FILENO);
	dup2(ttyfd, STDOUT_FILENO);
	dup2(ttyfd, STDERR_FILENO);
	close(ttyfd);
	execvp(cmd, args);
	donePty();
	exit(-1);
    }
    close(ttyfd);
    return 0;
}

int PtyProcess::openPty()
{
    int ptyfd = -1;
    int ttyfd;
    if ( openpty(&ptyfd,&ttyfd,ttynam,0,0) )
	ptyfd = -1;
    else
	close(ttyfd);
    if ( ptyfd < 0 ) {
	qApp->exit(1);
	return -1;
    }
    return ptyfd;
}

void PtyProcess::send_bytes(const char* s, int len)
{
  ::write(fd, s, len);	
}

void PtyProcess::send_string(const char* s)
{
  ::write(fd, s, strlen(s));
}

void PtyProcess::readPty()
{ 
  char buf[4096];

  int len = ::read( fd, buf, 4096 );

  if (len == -1)
     donePty();

  if (len < 0)
     return;

  buf[len]=0;

  emit block_in(buf,len);
}
