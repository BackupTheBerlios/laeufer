#ifndef _message_dispatcher_h
#define _message_dispatcher_h
#include "include.h"

#include <vector>
class Message;
class driver;
class bus_manager;
class bus;


/**
 * @short Dispatches the incoming messages and sends them to the drivers.
 * @author Markus Weimer <markus@weimo.de>
 * @see driver
 * @see bus_manager
 */

class message_dispatcher
{
public:

	/**
	 * Creates a new message_dispatcher for the
	 * given bus. This will also create a bus_manager
	 * for this bus.
	 *
	 * @param bus the bus to be used
	 *
	 */
	message_dispatcher(bus * message_bus);

#ifdef TRIVIAL_BUS
#warning "Hier ist noch debug-Code"
	message_dispatcher(bus_manager * BUSMASTER);
#endif
	/**
	 * The Destructor
	 *
	 */
	~message_dispatcher(void);

	/**
	 * registers a driver to this dispatcher/bus
	 *
	 * @param driver The driver to be registered
	 *
	 * @returns
	 * MD_REGISTER_FINE, if everything went fine.
	 * MD_REGISTER_ID_INVALID, if the id of the driver is not
	 * valid on  this bus. This may be because the device is not
	 * connected to the bus or because the id is out of range
	 * for this bus.
	 * MD_REGISTER_DRIVER_NULL, if the the given driver* was a NULL-Pointer
	 * MD_REGISTER_IDOFBROADCAST, if the given id was the id of the broadcast
	 *
	 */
	int register_driver(driver * drv);


	/**
	 * unregisters a driver
	 * Note: This does *not* delete the driver from Memory
	 *
	 * @param driver The driver to be unregistered.
	 *
	 */
	void unregister_driver( driver *drv);


	/**
	 * unregisters a driver
	 * Note: This does *not* delete the driver from Memory
	 *
	 * @param id The id of the driver to be unregistered.
	 *
	 */
	void unregister_driver( int id);


	/**
	 * check whether a driver exists for a given id
	 *
	 * @param id the id of the device to be checked
	 * @returns true, if an driver for the given id is registered.
	 * False, if the id was invalid or there is nor driver registered.
	 */
	bool driver_exists(int ID);

	/**
	 * Receive a new message and send it to the correct driver.
	 *
	 * This method makes heavy use of the logging-facility, so check
	 * the log if a message was not transmitted correctly to the driver.
	 * This method is used by the bus-framework.
	 *
	 * @param m the message to be received
	 */
	void receive(Message* m);

	/**
	 * sends a message to the bus.
	 * @param m: A message-Object to be sent.
	 * @see message
	 */
	void send(Message* m);

	/**
	 * returns the broadcast-id of the underlying bus
	 * this can be used to check, whether a specific
	 * id might be valid.
	 *
	 */
	int getBroadcastID(void);
	/**
	 * @return the maximum of id's allowed on the bus.
	 */
	int getIdLimit(void);

	enum errorcodes
	{

		// registering went fine
		REGISTER_FINE,

		// the id of the driver is not supported on the bus
		REGISTER_ID_INVALID,

		// the given pointer was NULL
		REGISTER_DRIVER_NULL,

		// the id of the driver is the broadcast-id on the bus
		REGISTER_IDOFBROADCAST
	};
private:
	// Just to create the drivers-Array/Vector
	void initDrivers(void);

	//The underlying bus
	bus_manager *busmaster;

	//The drivers
	vector<driver*> drivers;
};
#endif





