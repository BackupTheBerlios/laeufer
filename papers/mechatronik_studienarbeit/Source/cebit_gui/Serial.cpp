#include "Serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


Serial::Serial( const string& deviceName, const speed_t speed ){
  this->deviceName = deviceName;
  this->baudrate=speed;
}


Serial::~Serial(){
  close(fd);
}

void Serial::setBaudrate ( speed_t speed ){
  baudrate = speed;
}


speed_t Serial::getBaudrate( void ){
  return baudrate;
}

void Serial::send(const unsigned char data){
  write(fd, &data, 1);
}


bool Serial::openPort( void ){
  fd = open(deviceName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  
  /* Check, ob der Port aufmachbar ist */
  if (fd == -1) return false;
  
  fcntl(fd, F_SETFL, 0);
  
  /* Initialisierung */
  
  /************************
	Datenrate einstellen
  ***********************/
  tcgetattr(fd, &options);
  
  cfsetispeed(&options, baudrate);  //Input-Datenrate wird gesetzt
  cfsetospeed(&options, baudrate);  //Output-Datenrate wird gesetzt
  
  options.c_cflag |= (CLOCAL | CREAD);
  
  tcsetattr(fd, TCSANOW,&options);
  
  /************************
	 8N1 einstellen
  ************************/
  //Protokolltyp 8N1. es wird nur ein Byte übertragen, ohne Paritätsbit und ohne Handshake
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  options.c_iflag &= ~(IXON | IXOFF);
  
  tcsetattr(fd, TCSANOW,&options);
  
  /* Wenn wir hier sind, ist alles gut gegangen :-) */
  return true;
}
