/***************************************************************************
 bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#ifndef _BUS_H_
#define _BUS_H_

#include "include.h"

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
 * @version 0.1.0
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
	 * Transmits the message
	 * @param id Identifier of the device that is to be contacted
	 * @param op Operation to execute on the other device
	 * @param data Optional parameters to transmit. The pointer
	 * is assumed to have been allocated dynamically; responsibility
	 * passes to the bus implementation. May be NULL.
	 * @param length Number of parameters to transmit
	 * @return The maximum number of bytes (including id and op)
	 * that the bus can handle before it is full
	 */
	virtual int send(int id, int op, byte *data = NULL,
			 int length = 0) =0;


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
	 * @param id Pointer to an int that stores the incoming ID
	 * @param op Pointer to an int the incoming operation is stored in
	 * @param data Pointer to a sufficiently large buffer any optional
	 *             bytes will be passed to
	 * @param length Pointer to an int the number of optional bytes
	 *             stored in the 'data' pointer will be written to
	 * @returns 0 on success, an error code otherwise
	 */
	virtual int get_message(int *id, int *op, byte *data,
				int *length) =0;


	/**
	 * Retreives information about the bus
	 *
	 * @param broadcast_id Pointer to the value the universal broadcast
	 * ID (which, if passed to send(), will cause a broadcast rather
	 * than a directed message) will be written to
	 * @param id_limit The highest valid device ID, plus one.
	 * @param op_limit The highest valid operation number, plus one.
	 */
	virtual void get_id_setup(int *broadcast_id, int *id_limit, int *op_limit) =0;
};


#endif /* _BUS_H_ */
