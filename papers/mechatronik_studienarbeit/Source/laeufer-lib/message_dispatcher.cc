#include "message_dispatcher.h"
#include "include.h"
#include "bus.h"
#include "driver.h"
#include "bus_manager.h"
#include "message.h"


#ifdef TRIVIAL_BUS
#warning "Trivial BUS used!"
message_dispatcher::message_dispatcher(bus_manager * BUSMASTER)
{
	busmaster=BUSMASTER;
	//initialize the drivers-Array
	initDrivers();
}//message_dispatcher()
#endif

message_dispatcher:: message_dispatcher(bus * message_bus)
{
	//create the new bus_manager to be used
	busmaster = new bus_manager(*message_bus);
	initDrivers();

}//message_dispatcher()


inline void message_dispatcher::initDrivers(void)
{
	int idLimit=getIdLimit();
	for (int i=0; i<idLimit; i++)
	{
		drivers.insert(drivers.end(), NULL);
	}
}


message_dispatcher:: ~message_dispatcher(void)
{

}//~message_dispatcher()


int message_dispatcher::register_driver(driver * drv)
{
	/* check, whether the driver is ok */
	if(drv==NULL)
		return REGISTER_DRIVER_NULL;
	// Get  the id of this driver
	int id=drv->getID();

	// check the id for being the broadcast id
	if (id==getBroadcastID())
	{
		std::cerr << __FILE__ << ": The id to be registered ist the BROADCAST-ID giving up" << endl;
		return REGISTER_IDOFBROADCAST;
	}
	// now check whether the device with the given
	// id is connected to this bus
	if(!(busmaster->check_id_valid(id)))
		return REGISTER_ID_INVALID;

	/*if we reached this line, everything went fine
	and we can register the driver.*/
	drivers[id]=drv;
	drv->setMessageDispatcher(this);
	return REGISTER_FINE;
}//register_driver()


bool message_dispatcher::driver_exists(int ID)
{
	#warning "mit jameson absprechen"
	return ((busmaster->check_id_valid(ID)) && (drivers[ID] != NULL));
}


void message_dispatcher::receive(Message* m)
{
	if(m==NULL)
	{
		std::cerr << __FILE__ << ": message to be received is NULL. Giving up" <<endl;
		return;
	}
	int id = m->getId();
	int op = m->getOp();
	//Check whether the incoming transmission is a broadcast
	if(id == getBroadcastID())
	  {
		std::cerr <<__FILE__<<": Broadcast received. That shouldn't happen"<<endl;
		delete m;
		return;
	  }//if broadcast
	
	//check whether we have a driver for this device
	if(!driver_exists(id))
	  {
		std::cerr << __FILE__ ": No driver for id: " << id << endl;
		delete m;
		return;
	  }//if no driver
	
	//check whether the command is valid
	if(!(drivers[id]->valid_command(op)))
	  {
		std::cerr << __FILE__ << ": Command " << op << " not valid for driver " << id
				  << endl;
		delete m;
		return;
	  }//if command invalid
	
	drivers[id]->receive(m);
	
}//receive()

void message_dispatcher::send(Message* m)
{
  if (m==NULL)
	{
	  std::cerr << __FILE__ << ": Trying to send NULL-message. Giving up" << endl;
	  return;
	}
  //Just to be secure...
  m->lock();
  busmaster->send(m);
}


void message_dispatcher::unregister_driver( driver *drv)
{
  if (drv==NULL) return;
  unregister_driver(drv->getID());
}//unregister_driver()


void message_dispatcher::unregister_driver( int ID)
{
  //cerr << __FILE__ ": Unregistering Driver with id: " << ID << endl;
  
  //if there is no driver, we can return
  if(!(driver_exists(ID))) return;
  
  //Delete the entry of the driver
  drivers[ID]=NULL;
}//unregister_driver()

inline int message_dispatcher::getBroadcastID(void)
{
  return busmaster->get_broadcast_id();
}

inline int message_dispatcher::getIdLimit(void)
{
  return busmaster->get_id_limit();
}
