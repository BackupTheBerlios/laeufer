#include "notifier.h"
#include <qsocketnotifier.h>

notifier::notifier(int HANDLE, void F(void)){
  q = new QSocketNotifier(HANDLE, QSocketNotifier::Read, this);
  f = F;
}
void notifier::start( void ){
  QObject::connect(q, SIGNAL(activated(int)), this, SLOT(notify()));
}

void notifier::notify( void ){
  f();
}
