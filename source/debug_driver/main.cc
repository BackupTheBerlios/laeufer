#include "include.h"
#include <qapplication.h>
#include "debugTreiberGUIimpl.h"
int main( int argc, char **argv ){

  QApplication a(argc, argv);

  DebugTreiberGUIimpl x;
  

  a.setMainWidget( & x );
  x.show( );

  

  return a.exec();
}
