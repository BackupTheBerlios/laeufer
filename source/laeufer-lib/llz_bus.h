/***************************************************************************
 llz_bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#ifndef _LLZ_BUS_H_
#define _LLZ_BUS_H_

#include "bus.h"

/**
 * LLZ based bus implementation
 *
 * A bus implementation based on an LLZ bus running on a serial
 * port
 * 
 * @author creichen@rbg.informatik.tu-darmstadt.de
 * @version 0.1.0
 */

class llz_bus
{
public:
	virtual int init(bool *devices, bool **operations);

	virtual int send(message *msg);

	virtual int messages_waiting(void);

	virtual message *msg get_message(void);

	virtual void get_id_setup(int *broadcast_id, int *id_limit, int *op_limit);

	virtual vector<int> &
	get_pollers(int *delay);

	virtual void
	poll(void);

private:
	int fd;
	llz_llo_server *srv;
};


#endif /* _LLZ_BUS_H_ */
