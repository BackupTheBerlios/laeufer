/***************************************************************************
 bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#ifndef _BUS_MANAGER_H_
#define _BUS_MANAGER_H_

#include <queue>
#include "bus.h"
#include "include.h"
#include "message_dispatcher.h"
#include "message.h"

class message_dispatcher;

/**
 * Bus event queue and transmission manager
 * @author creichen@rbg.informatik.tu-darmstadt.de
 * @version 0.1.0
 */

struct bus_message
{
	int priority;
	int id;
	int op;
	byte *data;
	int data_size;
	int size;

	bool operator< (const bus_message &other) const
	{ return other.priority < priority; }
};

class bus_manager
{
public:
#ifdef TRIVIAL_BUS
  bus_manager(void);
#endif


	bus_manager(bus &internal_bus);
	~bus_manager(void);


	/**
	 * Initializes the bus associated with this manager
	 *
	 * @return zero on success, a bus error code otherwise
	 */
	int init(void);

	/**
	 * Adds a message to the queue of messages that are to be transmitted
	 *
	 * @param id Identifier of the device that is to be contacted
	 * @param op Operation to execute on the target device
	 * @param data Optional parameters to transmit. This is expected to
	 * be a static buffer; the bus_manager takes no responsibility for
	 * this pointer.
	 * @param length Number of parameters to transmit
	 * @param pri Optional transmission priority (defaults to NORMAL)
	 */
	/*void send(int id, int op, byte *data = NULL, int length = 0,
		 int pri = message::NORMAL_PRIO);*/

	void send(Message* m);

	/**
	 * Retreives the ID that can be used for message broadcasting
	 *
	 * @return The broadcast ID (always present)
	 */
	const int get_broadcast_id()
	{ return broadcast_id; }

	/**
	 * Retreives a number that is more than the maximum allowed ID number
	 *
	 * @return For a bus with n devices numbered from 0 to (n-1), this
	 * will return n.
	 */
	const int get_id_limit()
	{ return id_limit; }

	/**
	 * Sets the message dispatcher object for internal usage
	 *
	 * @param msg_dispatcher The message dispatcher to set
	 */
	void set_message_dispatcher(message_dispatcher &msg_dispatcher);

	/**
	 * Determines whether the specified device ID is valid in the current bus
	 *
	 * @param id Identifier of the device to check
	 * @return true if the device is present, false if it isn't
	 */
	bool check_id_valid(int id);

	/**
	 * Determines whether the specified operation is supported by a device
	 *
	 * @param id Identifier of the device to test
	 * @param op Operation to test for
	 */
	bool check_op_valid(int id, int op);

private:
	bus *internal_bus;
	message_dispatcher *dispatcher;
	priority_queue<bus_message> *message_queue;

	/* Bus-specific information */
	int broadcast_id;
	int id_limit;
	int op_limit;
	bool *devices;
	bool **operations;
};


#endif /* _BUS_MANAGER_H_ */





