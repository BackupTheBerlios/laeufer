/***************************************************************************
 mlp_bus.cc Copyright (C) 2001 Laeufer-Projekt, TU Darmstadt

 This program is provided WITHOUT WARRANTY of any kind, either expressed
 or implied, including but not limited to the warranties of merchantibility,
 noninfringement, and fitness for a specific purpose.

***************************************************************************/

#include <cstdio>
#include "mlp_bus.h"

/*#define IO_DEBUG*/

#define MLP_ORDER (6 << 5)
#define MLP_REPORT (7 << 5)

#define MLP_SERIAL_SOB 0xf0
#define MLP_SERIAL_EOB 0xf1
#define MLP_SERIAL_ESC 0xf2
#define MLP_SERIAL_ESC_MASK 0xf0
#define MLP_SERIAL_ESC_MIN 0xf0
#define MLP_SERIAL_ESC_MAX 0xf7

#define MLP_SERIAL_MUST_BE_ESCAPED(x) ((x >= MLP_SERIAL_ESC_MIN) && (x <= MLP_SERIAL_ESC_MAX))


/*********************************************************************
  MLP/serial protocol specification

  We are using a standard type 6 MLP V1 over CAN. The encoding we use
  for serial transmission, however, needs additional start-frame and
  end-of-frame code. For this, we reserve the bytes 0xf0 to 0xf7
  (which do correspond to MLP_REPORT messages to higher-ranking
  devices, but rarely occur in LLZ, where they are not used for
  commands, and LLO, where they correspond to protocol errors) as
  follows:

  0xf0 : [SOB] START OF BLOCK
  0xf1 : [EOB] END OF BLOCK
  0xf2 : [ESC] ESCAPE NEXT
	 Semantics are as follows: The "real" value of the next
	 byte equals that byte or'ed to 0xf0, thus allowing
         it to be transmitted

  0xf3--0xf7: Reserved for future applications


**********************************************************************/


static int /* length */
mlp_serialize_message(byte *dest, int length, const mlp_message_t &src)
{
	int i;
	int pos = 0;

	dest[pos++] = MLP_SERIAL_SOB;

	for (i = 0; i < length; i++) {
		byte c = src.data[i];

		if (MLP_SERIAL_MUST_BE_ESCAPED(c)) {
			dest[pos++] = MLP_SERIAL_ESC;
			dest[pos++] = (c & ~MLP_SERIAL_ESC_MASK);
		} else
			dest[pos++] = c;
	}

	dest[pos++] = MLP_SERIAL_EOB;

	return pos;
}

static int
mlp_deserialize_message(mlp_message_t &dest, int len, byte *src)
{
	int pos = 0;
	int writepos = 0;

	while (src[++pos] != MLP_SERIAL_EOB) {
		byte c = src[pos];

		if (c == MLP_SERIAL_ESC)
			c = src[++pos] | MLP_SERIAL_ESC_MASK;

		if (writepos >= MLP_MESSAGE_SIZE) {
			int i;
			fprintf(stderr, "MLP-deserialize: Message too long!\n Message was: [");
			for (i = 0; i < len; i++)
				fprintf(stderr, "%02x ", 0xff & src[i]);
			fprintf(stderr, "]\n");

			return -1;
		}
		dest.data[writepos++] = c;
	}

	return 0;
}

mlp_bus::~mlp_bus()
{
}

mlp_bus::mlp_bus(string devname, int rate)
{
	fd_name = devname.c_str();
	baudrate = rate;
	this->start_of_message = -1;
}

int
mlp_bus::init(bool *devices, bool **operations)
{
	termios options;
	int i, j;

	fd = open(fd_name, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
  
	if (fd == -1) {
		perror("MLP:init");
		return BUS_ERROR_FATAL;
	}
  
	/*	fcntl(fd, F_SETFL, 0); */
	fcntl(fd, F_SETFL, FASYNC);
  
	/* Initialize data rate */
	tcgetattr(fd, &options);
  
	cfsetispeed(&options, baudrate);  /* Input-Datenrate wird gesetzt */
	cfsetospeed(&options, baudrate);  /* Output-Datenrate wird gesetzt */
  
	options.c_cflag |= CLOCAL | CREAD;
  
	tcsetattr(fd, TCSANOW, &options);
  
	/* Switch to 8N1 */
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_iflag &= ~(IXON | IXOFF | IGNBRK );
	options.c_lflag &= ~(ICANON | ISIG | IEXTEN);
  
	tcsetattr(fd, TCSANOW, &options);

	for (i = 0; i < 16; i++)
		devices[i] = true;

	for (i = 0; i < 16; i++)
		for (j = 0; j < 128; j++)
			operations[i][j] = true;

	partial_msg_pos = 0;


	return 0; /* success */
}


int
mlp_bus::send(int id, int op, byte *data = NULL,
	      int length = 0)
{
	byte msg_buf[MLP_MESSAGE_SIZE << 1];
	mlp_message_t buf;

	buf.data[0] = MLP_ORDER | id;
	buf.data[1] = op;

	if (length > MLP_MESSAGE_SIZE - 2) {
		cerr << "MLP: More than " << MLP_MESSAGE_SIZE - 2 << " bytes of arguments not supported!\n";
		throw new string("MLP: More than 5 bytes of arguments not supported");
	}

	if (data && length)
		memcpy(buf.data + 2, data, length);

	int msglen = mlp_serialize_message(msg_buf, MLP_MESSAGE_SIZE, buf);
	if (write(fd, &msg_buf, msglen) < msglen) {
		perror("MLP:send");
		return BUS_ERROR_GENERIC;
	}

#ifdef IO_DEBUG
	fprintf(stderr, "{[<<-- ");
	for (int i = 0; i < msglen; i++)
		fprintf(stderr, "%02x ", msg_buf[i]);
	fprintf(stderr, "]}\n");
#endif

	return 0;
}


int recv_count = 0;

int
select_read(int fd, unsigned char *dest, int maxread)
{
	struct timeval tv;
	int rv;
	fd_set fds;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_SET(fd, &fds);
	rv = select(fd+1, &fds, NULL, NULL, &tv);

	if (rv <= 0) /* No input or error */
		return rv;
	else
		return read(fd, dest, maxread);
}

int
mlp_bus::messages_waiting()
{
	int maxread = MLP_MAX_BUF_SIZE - partial_msg_pos;
	int got_bytes = select_read(fd, (unsigned char *) (&partial_message + partial_msg_pos),
				    maxread);

	if (got_bytes > 0) {
		for (int j = partial_msg_pos; j < partial_msg_pos + got_bytes; j++) {
			byte b = partial_message[j];
#ifdef IO_DEBUG
			fprintf(stderr, "{{ %d:%02x }}", recv_count++, 0xff & b);
#endif
			if (b == MLP_SERIAL_SOB
			    && this->start_of_message < 0)
				start_of_message = j;
			else if (b == MLP_SERIAL_EOB) {
				mlp_message_t msg;
				if (mlp_deserialize_message(msg, j - start_of_message + 1, partial_message + start_of_message))
					return BUS_ERROR_FATAL;
				msg_queue.push_front(msg);
				start_of_message = -1;
			}
		}
	}
	fprintf(stderr, "Received %d bytes.\n", got_bytes);

	if (start_of_message > (MLP_MAX_BUF_SIZE >> 1)) {
		int delta = start_of_message;
		start_of_message = 0;
		partial_msg_pos -= delta;
		if (partial_msg_pos)
			memmove(partial_message, partial_message + delta, partial_msg_pos);
	}

	if (got_bytes < 0) {
		perror("MLP:poll-message");
		return BUS_ERROR_FATAL;
	}

	return msg_queue.size();
}

int
mlp_bus::get_message(int *id, int *op, byte *data,
		     int *length)
{
	mlp_message_t msg;
	int rv = messages_waiting(); /* Also polls for messages */
	if (rv == 0)
		return BUS_ERROR_NO_MORE_MESSAGES;
	else if (rv < 0)
		return rv;

	msg = msg_queue.back();
	msg_queue.pop_back();

	*id = msg.data[0] & 0x1f;
	*op = msg.data[1];
	*length = MLP_MESSAGE_SIZE - 2;
	memcpy(data, msg.data + 2, *length);
	return 0;
}


void
mlp_bus::get_id_setup(int *broadcast_id, int *id_limit, int *op_limit)
{
	*broadcast_id = MLP_BCAST_ID;
	*id_limit = MLP_MAX_ID;
	*op_limit = MLP_MAX_OP;
}

