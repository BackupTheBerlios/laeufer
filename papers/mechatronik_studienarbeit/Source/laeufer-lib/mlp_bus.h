/***************************************************************************
 mlp_bus.h Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#ifndef _MLP_BUS_H_
#define _MLP_BUS_H_

#include <termios.h>
#include <unistd.h>
#include "bus.h"
#include <deque.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MLP_MESSAGE_SIZE 7
#define MLP_BCAST_ID 0
#define MLP_MAX_ID 31
#define MLP_MAX_OP 127

typedef struct {
	byte data[MLP_MESSAGE_SIZE];
} mlp_message_t;

/**
 * MLP bus and protocol access interface for short messages
 *
 * This bus encapsulates both hardware access and the sofware
 * protocols used for transmission.
 * 
 * @author creichen@rbg.informatik.tu-darmstadt.de
 * @version 0.1.0
 */
class mlp_bus: public bus
{
public:
	mlp_bus(string dev_name, int baudrate = B115200);
	/** Creates a new MLP bus for an existing serial system device
	 * @param dev_name: Name of the device file
	 * @param baudrate: Port baud rate
	 */

	~mlp_bus();
	/** Destroys the MLP bus
	 */

	virtual int init(bool *devices, bool **operations);


	virtual int send(int id, int op, byte *data = NULL,
			 int length = 0);


	virtual int messages_waiting();

	virtual int get_message(int *id, int *op, byte *data,
				int *length);


	virtual void get_id_setup(int *broadcast_id, int *id_limit, int *op_limit);
private:

	static const int MLP_MAX_BUF_SIZE = 1024;
	const char *fd_name;
	int baudrate;

	int fd;
	int partial_msg_pos;
	int start_of_message;
	byte partial_message[MLP_MAX_BUF_SIZE];
	deque<mlp_message_t> msg_queue;
};


#endif /* _BUS_H_ */
