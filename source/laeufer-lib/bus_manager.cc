/***************************************************************************
 bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either
 expressed or implied, including but not limited to the warranties of
 merchantibility, noninfringement, and fitness for a specific purpose.

***************************************************************************/


#include "bus_manager.h"
#include <queue>


static bus *active_bus = NULL;

static void
poll_func(void)
{
	bus->poll();
}


#ifdef TRIVIAL_BUS
#warning "Using trivial bus_manager"
bus_manager::bus_manager(void)
{
  broadcast_id=0;
  id_limit=32;
  op_limit=64;
}

bus_manager::bus_manager(bus &internal_bus)
{
  broadcast_id=0;
  id_limit=32;
  op_limit=64;
}


bus_manager::~bus_manager(void)
{
}


int bus_manager::init(void)
{
}

void bus_manager::send(message* m)
{
	dispatcher->receive(m);
}


void bus_manager::set_message_dispatcher(message_dispatcher &msg_dispatcher) 
{
	dispatcher = &msg_dispatcher;
}


bool bus_manager::check_id_valid(int id)
{
	return (id<get_id_limit());
}


bool bus_manager::check_op_valid(int id, int op)
{
	return true;
}



#else // keine Testumgebung mehr

/********************************************************/
/*		Real bus implementation 		*/
/********************************************************/


bus_manager::bus_manager(bus &internal_bus)
{
        int i;
	this->internal_bus = &(internal_bus);
	dispatcher = NULL;
	this->internal_bus->get_id_setup(&broadcast_id, &id_limit, &op_limit);
	message_queue = new priority_queue<bus_message>;

	if (id_limit < 1 || op_limit < 1) {
	  cerr << __FILE__": Error: Bus reported id_limit=" << id_limit << " and op_limit=" << op_limit << endl;
	  return;
	}

	devices = new bool[id_limit];
	operations = new bool*[id_limit];

	for (i = 0; i < id_limit; i++) {
		devices[i] = false;

		operations[i] = new bool[op_limit];
		for (int j = 0; j < op_limit; j++)
			operations[i][j] = false;
	}
}

bus_manager::~bus_manager(void)
{
	delete message_queue;

	delete[] devices;
	for (int i = 0; i < id_limit; i++)
		delete[] operations[i];
	delete[] operations;
}


int bus_manager::init(void)
{
	return internal_bus->init(devices, operations);
}

void
bus_manager::send(message *msg)
{
	byte *buf = (length)? new byte[length] : NULL;
	bus_message *bmessage;
	
	if (length)
		memcpy(buf, data, length);

	message = new bus_message;
	bmessage->priority = pri;
	message->op = op;
	message->data = buf;
	message->data_size = length;
	message->id = id;

	message_queue->push(*message);
}

void
bus_manager::set_message_dispatcher(message_dispatcher &msg_dispatcher) 
{
	dispatcher = &msg_dispatcher;

	/* Now assert regular polling of the bus, if requested */
	int poll_time;
	vector <int> poller_fds = internal_bus.get_pollers(&poll_time);
	bool need_polling;

	need_polling = (poll_time || poller_fds.size());

	if (need_polling) {
		if (bus_manager)
			cerr << DBG <<"message dispatcher set more than once!";

		if (poll_time) {
			cerr << DBC "UNSUPPORTED: poll_time=" << poll_time << " > 0!";
			exit(1);
		}

		active_bus = internal_bus;

		for (vector<int>::iterator it = poller_fds.begin();
		     it != polled_fds.end(); it++) {
			int fd = *it;
			msg_dispatcher.notify(fd, &poll_func);
		}
	}
}


bool
bus_manager::check_id_valid(int id)
{
	if (id < 0 || id >= id_limit)
		return false;
	return devices[id];
}

bool
bus_manager::check_op_valid(int id, int op)
{
	if (id < 0 || id >= id_limit
	    || op < 0 || op >= op_limit)
		return false;

	return operations[id][op];
}

#endif //TRIVIAL_BUS

#ifdef TEST
int
main(int argc, char **argv)
{
}

#endif






