#include "message.h"

Message::Message(void){
  locked=false;
  dataPresent=false;
  setPri(-1);
  setOp(-1);
  setId(-1);
}//Message()


Message::~Message(void){
}// Message()


/********************************
 getX()
*********************************/
int Message::getPri(void){
  return pri;
}//getPRI()


int Message::getId(void){
  return id;
}//getID()


int Message::getOp(void){
  return op;
}//getOP()


vector<byte> Message::getData(void){
  return data;
}//getDATA()


/********************************
 setX()
*********************************/
void Message::setId(int ID){
  if(!locked) id = ID;
}//setID()


void Message::setOp(int OP){
  if(!locked) op = OP;
}//setOP()


void Message::setData( vector<byte> DATA ){
  if(locked) return;
  data = DATA;
  dataPresent = true;
}//setDATA()


void Message::setPri(int PRI){
  if(!locked) pri = PRI;
}//setPRI()


void Message::lock(void){
  locked=true;
}//lock()


bool Message::isLocked(void){
  return locked;
}//islocked()

bool Message::hasData(void){
  return dataPresent;
}


bool Message::operator< (Message &other){
  return other.getPri() < getPri();
}
