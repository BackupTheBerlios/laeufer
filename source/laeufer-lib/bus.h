/***************************************************************************
 bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#ifndef _BUS_H_
#define _BUS_H_

#include "include.h"
#include "message.h"

/* Broadcast address */
#define MSG_BROADCAST 0

#define BUS_ERROR_FATAL -1 /* Bus unable to operate; requests termination */
#define BUS_ERROR_GENERIC -2
#define BUS_ERROR_QUEUE_FULL -3
#define BUS_ERROR_NO_MORE_MESSAGES -4


/**
 * Generic bus and protocol access interface for short messages
 *
 * This bus encapsulates both hardware access and the sofware
 * protocols used for transmission.
 * 
 * @author creichen@rbg.informatik.tu-darmstadt.de
 * @version 0.2.0
 */

class bus
{

public:
	/**
	 * Initializes the bus
	 *
	 * Performs initialization on the bus, detects all devices
	 * present and the operations they support
	 *
	 * @param devices Pointer to a list of boolean values that are
	 * set to true iff the devices are present in the list. The
	 * list of devices is expected to have been initialized before
	 * that.
	 * @param operations Pointer to a list of pointers to lists of
	 * boolean values describing whether the device/operation tuple
	 * deominating the index is valid.
	 * @return zero on success, an error code otherwise
	 */
	virtual int init(bool *devices, bool **operations) =0;


	/**
	 * Transmits a message
	 *
	 * @param msg The message to transmit
	 */
	virtual int send(message *msg) =0;


	/**
	 * Returns the number of incoming messages waiting to be delivered
	 *
	 * @return The number of incoming messages. Implementations not
	 * supporting counting these may simply return >0 if at least
	 * one message is incoming.
	 */
	virtual int messages_waiting() =0;


	/**
	 * Retreives an incoming message
	 *
	 * @return The next message in the queue of incoming messages,
	 * or NULL if no message is in there.
	 */
	virtual message *get_message(void) =0;


	/**
	 * Retreives information about the bus
	 *
	 * @param broadcast_id Pointer to the value the universal broadcast
	 * ID (which, if passed to send(), will cause a broadcast rather
	 * than a directed message) will be written to
	 *
	 * @param id_limit The highest valid device ID, plus one.
	 * @param op_limit The highest valid operation number, plus one.
	 */
	virtual void get_id_setup(int *broadcast_id, int *id_limit, int *op_limit) =0;


	/**
	 * Retreives the information about how the bus wants to be polled
	 *
	 * @returns A vector of all file handles the bus wants to be polled on
	 * @returns *delay: The number of microseconds to wait between polls,
	 * or 0 if no timed polls are needed or used
	 */
	virtual vector<int> &
	get_pollers(int *delay);
	

	/**
	 * Does regular bus maintenance and polling
	 */
	virtual void
	poll(void);
};


#endif /* _BUS_H_ */
