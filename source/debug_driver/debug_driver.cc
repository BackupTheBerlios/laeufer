#include "debug_driver.h"
#include <iostream>
#include "message.h"

debug_driver::debug_driver(int ID)
  : driver()
{
  setID(ID);
  lastMessage=NULL;
}


bool debug_driver::receive(message* m)
{
  lastMessage=m;
  emit messageReceived();
  return true;
}


bool debug_driver::valid_command(int op)
{
  return true;
}


message* debug_driver::getLastMessage(void)
{
  return lastMessage;
}
