#include "message.h"

message::message(void){
  locked=false;
  dataPresent=false;
  setPri(-1);
  setOp(-1);
  setId(-1);
}//message()


message::~message(void){
}// message()


/********************************
 getX()
*********************************/
int message::getPri(void){
  return pri;
}//getPRI()


int message::getId(void){
  return id;
}//getID()


int message::getOp(void){
  return op;
}//getOP()


vector<byte> message::getData(void){
  return data;
}//getDATA()


/********************************
 setX()
*********************************/
void message::setId(int ID){
  if(!locked) id = ID;
}//setID()


void message::setOp(int OP){
  if(!locked) op = OP;
}//setOP()


void message::setData( vector<byte> DATA ){
  if(locked) return;
  data = DATA;
  dataPresent = true;
}//setDATA()


void message::setPri(int PRI){
  if(!locked) pri = PRI;
}//setPRI()


void message::lock(void){
  locked=true;
}//lock()


bool message::isLocked(void){
  return locked;
}//islocked()

bool message::hasData(void){
  return dataPresent;
}


bool message::operator< (message &other){
  return other.getPri() < getPri();
}
