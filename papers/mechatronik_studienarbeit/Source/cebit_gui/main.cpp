#include "include.h"
#include <qpe/qpeapplication.h>
#include <qapplication.h>
#include "GoRide.h"
#include "Serial.h"

int main( int argc, char **argv )
{
  QPEApplication a(argc, argv);
  GoRide x;
  a.setMainWidget(&x);
  x.enableFullscreen();
  //x.show();
  //x.showMaximized();
  
  return a.exec();
}
