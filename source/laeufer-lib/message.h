#ifndef _MESSAGE_H
#define _MESSAGE_H
#include "include.h"
#include <vector>

/**
 *
 * @short Baseclass for messages that are sent on the bus
 *
 * @author Markus Weimer <markus@weimo.de>
 */
class message{


 public:


  /**
   * Constructs a new message-object
   */
  message(void);


  /**
   * Destructor
   */
  ~message(void);

  
  /**
   * @return the id of the Message
   */
  int getId(void);

  
  /**
   * Sets the Operation of the Message.
   *
   * @param OP the operation.
   */
  void setOp(int OP);
  

  /**
   * @return the operation
   */
  int getOp(void);
  

  /**
   * Sets the (optional) Data-Bytes to be send.
   *
   * Use this method to set the extra bytes you want to send to your device.
   *
   * @param data the data-bytes to be transmitted.
   *
   *
   */
  void setData( vector<byte> data );
  

  /**
   * Returns the databytes transmitted
   *
   * @return the databytes transmitted
   */
  vector<byte> getData(void);

  
  /**
   * set the Priority of this Message
   *
   * @param PRI the priority to be used.
   */
  void setPri(int PRI);
  

  /**
   * @return the priority of this Message
   */
  int getPri(void);
  
  
  /**
   * locks the Message for changes. As there is
   * no unlock()-method, this is final.
   */
  void lock(void);
  
  
  /**
   * Checks, whether this Message is locked
   *
   * @return true, if so.
   */
  bool isLocked( void );
  
  
  /**
   * check whether the Message holds data
   *
   */
  bool hasData( void );
  
  
  /**
   * for internal use only.
   */
  bool operator< (message &other);
  
  
  /**
   * possible priorities:
   * VERY_HIGH_PRIO
   * HIGH_PRIO
   * NORMAL_PRIO
   * INFO_PRIO
   * LOW_PRIO
   * These may be set using the setPRI()-method
	 */
  enum prio
	{
	  VERY_HIGH_PRIO,	/* Transmit to the bus ASAP */
	  HIGH_PRIO,	/* Transmit with increased priority*/
	  NORMAL_PRIO,	/* Guaranteed transmission */
	  INFO_PRIO,	/* Lower-priority transmission */
	  LOW_PRIO	/* Least-priority transmission */
	  /* Priority 3 and 4 Messages are NOT GUARANTEED to reach the recipient-
		 they may be discarded if the bus load is too high.  */
	};
  

  /**
   * Set the id of the Message.
   *
   * This is the id of the device/driver-combination that wants to
   * communicate.
   *
   * @param ID the id to be set.
   */
  void setId( int ID );
  
  

  
  
 private:
  int id;
  int op;
  int pri;
  bool locked;
  vector<byte> data;
  bool dataPresent;
};
#endif

