#ifndef _message_dispatcher_h
#define _message_dispatcher_h
#include "include.h"

#include <vector>
class message;
class driver;
class bus_manager;
class bus;
class notifier;

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
   * @param message_bus the bus to be used
   *
   */
  message_dispatcher(bus * message_bus);

#ifdef TRIVIAL_BUS
#warning "Hier ist noch debug-Code"
  /**
   * DEBUG method only.
   *
   * used only while testing
   * @param BUSMASTER the bus_manager used by this message_dispatcher
   *
   */
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
   * @param drv The driver to be registered
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
   * @param drv The driver to be unregistered.
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
   * @param ID the id of the device to be checked
   * @returns true, if an driver for the given id is registered.
   * False, if the id was invalid or there is no driver registered.
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
  void receive( message *m );
  

  /**
   * sends a message to the bus.
   *
   * @param m A message-Object to be sent.
   * @see message
   */
  void send( message *m );
  
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


  /**
   * Starts a file-watching on the file given as file_handle and starts the
   * function F when the file changes.
   *
   * @param file_handle The file handle to watch
   * @param F(void) a pointer to the function to call, when the file changes
   */
  bool notify(int file_handle, void (*F)( void ) );


  /**
   * Errorcodes used by register_driver().
   */
  enum errorcodes {
	REGISTER_FINE, /**< registering went fine*/
	
	REGISTER_ID_INVALID, /**< the id of the driver is not supported on the bus*/
	
	REGISTER_DRIVER_NULL, /**<the given pointer was NULL */
	
	REGISTER_IDOFBROADCAST /**< the id of the driver is the broadcast-id on the bus */
  };


 private:
  /**
   * Just to create the drivers-Array/Vector.
   */
  void initDrivers(void);
  
  bus_manager *busmaster; /**< The bus_manager used by this message_dispatcher */
  
  vector<driver*> drivers; /**< The Drivers */
  
  notifier* noti;  /**< The notifier to be used by notify()*/
};
#endif





