/****************************************************************************************
 * (c) Cacko Team,2002,2003								*
 * Kino2 video player									*
 * http://www.cacko.biz									*
 ****************************************************************************************/

#include "player.h"
#include <qpe/qpeapplication.h>

int main( int argc, char ** argv )
{
    QPEApplication a( argc, argv );
    Player player;
    
    a.setMainWidget( &player );
    player.showMaximized();

    return a.exec();
}
