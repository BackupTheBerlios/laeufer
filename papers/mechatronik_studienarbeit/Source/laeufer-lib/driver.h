#ifndef _driver_h
#define _driver_h
#include <qobject.h>

class bus_manager;
class message_dispatcher;
class Message;

/**
 * This class provides the framework for writing drivers for the mechatronics
 * system. The drivers are used to make a connection between the high-level
 * things like gui, logics etc. and the low-level functionality of the
 * hardware.
 *
 * Any driver that will be used in the mechatronics of the "Läufer" has to be
 * derived from this class to make use of this framework. Just write your
 * driver as an  subclass
 * of this one and use the send() method to send messages to your device. See
 * the class "message" for details on how to create and use message-objects.
 * When your  device sends your driver a message, it is transmitted to the
 * receive()-method of your  driver, so add your code for handling specific
 * messages in this method. Before  transmitting any message to this method,
 * the framework will check with valid_command() whether  the message will be
 * accepted by this driver, so keep this method up to date.
 *
 * !IMPORTANT! Memory Management:
 * When sending a message, you are no longer responsible for the memory
 * allocated for this message-object. The memory-management for sending messages
 * is done by the  framework. Also, it is not possible to change a message after
 * it has been send, so when  sending a new message, create one using the new
 * message() operator. When receiving a message, you ARE responsible for the
 * memory allocated by  this message, so please delete it, when you no longer
 * need this message. You can use the  delete operator to accomplish this.
 *
 * In this framework, we use the concept of "communicating state machines",
 * where there are two state-machines: one on the embedded device and one
 * in the driver. Everytime the status changes in one state-machine, it informs
 * the other about the switch. The state-machine of the driver is less powerfull
 * and has less states than the one in the embedded device. Let's take a look on
 * a directional light: The state machine in the embedded device needs at least
 * two states: on, off, while the one in the driver needs only one: blinking.
 * Everytime something interesting happens to the state-machine, it informs the
 * other. The  device may be broken, so it is in state "broken" and sends the
 * message "I'm broken" to the other state-machine in the driver. Another
 * example is: The GUI sends the driver the signal to turn off the light, so the
 * state of the driver changes to "non-blinking". Obviously, this is an
 * interesting information for the other state-machine that is in state
 * "on-off-on-...", so it tells the embedded device "switch off". The
 * communication used in this system is based on operations and parameters. See
 * the message-class for information on how to create a message. You can use the
 * send()-function provided in this class to send a message to the device
 * associated with this driver
 *
 * @short baseclass for drivers
 * @author Markus Weimer <markus@weimo.de>
 * @see message
 */
class driver: public QObject {
  
  Q_OBJECT

public:
  /**
   * Constructor.
   *
   * Any derived subclass has to set the variable "id" int its constructor.
   * This uniqe id is used to make the connection between the device connected
   * to the bus and this driver.
   *
   * The id set on the device has to be the same as the id given here. Any
   * subclass of this one is unable to change the id more than once in the
   * object's lifecycle. So use with care.
   *
   */
  driver(void);
  
  /**
   * Set the Message Dispatcher.
   *
   * This method sets the message-dispatcher used by this class for sending
   * messages to the bus.
   *
   * It is used by the message dispatcher in the register()-process.
   *
   */
  void setMessageDispatcher(message_dispatcher* M);

  /**
   * Receives data from the bus.
   *
   * This method has to be implemented by any subclass to handle incoming
   * messages which were sent by the device asociated with this driver.
   *
   * IMPORTANT: You are responsible for the memory allocated by the
   * message received via this method. So you have to do a "delete m"
   * after processing it to keep the laeufer driving.
   
   * @param m a pointer to the message object that has been
   * received. You have to free the memory used by this message via
   * "delete m", for example.
   */
  virtual bool receive(Message* m)=0;

  /**
   * This method allows access to the id of the driver.
   *
   * It is used by the message-dispatcher in the process of
   * registering the driver.
   *
   * @return id of the device handeled by this driver
   *
   */
  int getID(void);
  
  
  /**
   * This method is used by the message dispatcher classes to check,
   * whether a specific command is supported by the driver BEFORE the
   * message is transmitted to the driver. So keep this method up to
   * date OR make your receive() tollerant for non-existing commands.
   *
   *
   * @return true, if the command is valid, false otherwise
   */
  virtual bool valid_command(int op)=0;
  
  
 protected:
  /**
   * Sends a message to the device of this driver.
   *
   * ATTENTION: This method will cause a segfault, if the driver
   * has not yet been registered with an messageDispatcher.
   *
   * The message passed to this method has to be setup with the
   * id of this driver.
   *
   * @param m A pointer to the message-object to be sent.
   * Do not touch this message any more, after you called
   * this method. It will be locked. You are NOT responsibble for
   * the memory allocated by this message. It will be deleted by
   * the driver framework for you.
   *
   */
  void send(Message* m);
  
  /**
   * convenience-function for sending messages.
   *
   * @param op The Operation to be transmitted
   *
   */
  void send(int op);
  
  
  /**
   * Sets the id of this driver.
   *
   * This id is the unique common identifier for this driver and the
   * device associated with it. It has to be set by any subclass of
   * this class in the constructor to the correct value. Do not change
   * this id at any other place.
   *
   * @param ID the id to be set.
   */
  void setID(int ID);
  
 private:
  /**
   * The message-dispatcher to be used.
   *
   * This object is needed for sending messages by the drivers.
   */
  message_dispatcher * md;

  /**
   * The id of this driver.
   *
   * This id is the unique common identifier for this driver and the
   * device associated with it. It has to be set by any subclass of
   * this class in the constructor to the correct value. Do not change
   * this id at any other place.
   *
   */
  int id;
  bool idLocked;
};
#endif
