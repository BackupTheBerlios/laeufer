/***************************************************************************
 bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#include "llz_bus.h"

#define DISCARD_FAILURES

llz_bus::~llz_bus
{
	delete srv;
}


int
send(message *msg)
{
	srv->send_command(msg);
}

int
messages_waiting(void)
{
	return srv->get_nr_waiting();
}

message *
llz_bus::get_message(void)
{
	return srv->get_incoming();
}

void
llz_bus::get_id_setup(int *bc_id, int *id_lim, int *op_lim)
{
	*bc_id = 0;
	*id_lim = LLO_MAX_PORT_NR;
	*op_lim = LLZ_MAX_CMD;
}

vector <int> &
llz_bus::get_pollers(int *delay)
{
	vector<int> retval(1);
	retval[0] = fd;
	*delay = 0;
	return retval;
}

llz_bus::poll()
{
	srv->poll();

#ifdef DISCARD_FAILURES 
#warning "Failed messages are being discarded with this setup!"
	message *msg;
	while (msg = srv->get_failed()) {
		free(msg);
	}
#endif
}
