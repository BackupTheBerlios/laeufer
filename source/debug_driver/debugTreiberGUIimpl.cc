#include "debugTreiberGUIimpl.h"

#include <iostream>

#include <qapplication.h>
#include <qspinbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>

#include "include.h"
#include "message_dispatcher.h"
#include "debug_driver.h"
#include "message.h"
#include "bus_manager.h"

DebugTreiberGUIimpl::DebugTreiberGUIimpl( QWidget* parent = 0, const char* name
										  = 0, WFlags fl = 0 )
  : DebugTreiberGUI(parent, name, fl)
{
  
  maximumBytes=toLength->maxValue();
  
  md = NULL;
  treiber = NULL;
#warning "Hier wird ein fake-busmanager erstellt"
  //Create the fake bus_manager
  bus_manager* bm = new bus_manager();
  
  // Create the message-dispatcher we'll
  // abuse for sending
  md = new message_dispatcher(bm);
  bm->set_message_dispatcher(*md);
  
  // Create a "hacked driver" which receives the data
  // for us
  setID(1);
  
  
  //Now collect all the nice Byte-Inputs to an Array
  bytes.resize(maximumBytes);
  rbytes.resize(maximumBytes);
  
  bytes[0]=byte0;
  bytes[1]=byte1;
  bytes[2]=byte2;
  bytes[3]=byte3;
  bytes[4]=byte4;
  bytes[5]=byte5;
  bytes[6]=byte6;
  bytes[7]=byte7;
  bytes[8]=byte8;
  bytes[9]=byte9;
  bytes[10]=byte10;
  bytes[11]=byte11;
  bytes[12]=byte12;
  bytes[13]=byte13;
  bytes[14]=byte14;


  //Now collect all the nice Rbyte-Inputs to an Array
  
  rbytes[0]=rbyte0;
  rbytes[1]=rbyte1;
  rbytes[2]=rbyte2;
  rbytes[3]=rbyte3;
  rbytes[4]=rbyte4;
  rbytes[5]=rbyte5;
  rbytes[6]=rbyte6;
  rbytes[7]=rbyte7;
  rbytes[8]=rbyte8;
  rbytes[9]=rbyte9;
  rbytes[10]=rbyte10;
  rbytes[11]=rbyte11;
  rbytes[12]=rbyte12;
  rbytes[13]=rbyte13;
  rbytes[14]=rbyte14;
  
}

DebugTreiberGUIimpl::~DebugTreiberGUIimpl(void)
{
}

void DebugTreiberGUIimpl::send( void )
{
  message* m = new message();
  
  //Variablen auslesen
  
  // ID
  if(broadcast->isChecked())
    {
      m->setId(md->getBroadcastID());
    }
  else
    {
      m->setId(DeviceID->value());
    }
  
  //Operation
  m->setOp(toOpId->value());
  m->setPri(message::NORMAL_PRIO);
  
  //Die Datenbytes aufbereiten
  int length = toLength->value();
  if(length>0)
    {
      std::vector<byte> data(length);
      for(int i=0; i<length;i++)
		{
		  data[i]=bytes[i]->value();
		}//for()
      m->setData(data);
    }//if(length>0)
  
  
  //Die nachricht locken.
  m->lock();
  
  // und absenden
  md->send( m );
  
  
}//send()



void DebugTreiberGUIimpl::setNumberOfDataBytes(int x)
{
  // Security-check
  if (x>maximumBytes) x=maximumBytes;
  
  int i=0;
  
  for(i=0;i<x;i++)
    bytes[i]->setEnabled(true);
  for(;i<maximumBytes;i++)
    bytes[i]->setDisabled(true);
  
}//setNumberOfDataBytes()


void DebugTreiberGUIimpl::newMessage(void)
{
  // get the Message out of the driver
  message* m = treiber->getLastMessage();
  message x = *m;
  
  // flush the Message, as this memory is not needed anymore.
  delete m;
  
  // add the Message to the vector of received Messages
  messages.insert(messages.end(),x);
  
  if(Pause->isChecked())
    return;
  
  //Update the GUI
  int aktuelleMessage=messages.size() - 1;
  receiveNumber->setMaxValue(aktuelleMessage);
  
  if (aktuelleMessage==0)
    showReceivedWithNumber(0);
  else
    receiveNumber->setValue(aktuelleMessage);
  
}//newMessage()


void DebugTreiberGUIimpl::setID(int x)
{
  // unregister the driver
  md->unregister_driver(treiber);
  
  // free the memory
  delete treiber;
  
  // create a new one
  treiber= new debug_driver(x);
  
  // register the new driver at the messagedispatcher
  md->register_driver(treiber);
  
  // connect the driver to this GUI
  connect( treiber, SIGNAL(messageReceived()), this, SLOT(newMessage()));
  
}//setID()


void DebugTreiberGUIimpl::showReceivedWithNumber(int x)
{
  int numberOfBytes=0;
  int i=0;
  std::vector<byte> data;
  
  message toshow = messages[x];
  fromOpId->setValue(toshow.getOp());
  
  if(toshow.hasData())
    {
      data = toshow.getData();
      numberOfBytes=data.size();
    }
  
  for(i=0;i<numberOfBytes;i++)
    rbytes[i]->setValue(data[i]);
  for(;i<maximumBytes;i++)
    rbytes[i]->setValue(0);
}//showReceivedWithNumber()


void DebugTreiberGUIimpl::quit()
{
  qApp->quit();
}//quit()

