#ifndef SERIAL_H
#define SERIAL_H
#include <termios.h>
#include <string>
class Serial{
public:
	Serial(const string& deviceName="/dev/ttySA0", speed_t speed=B115200);
	~Serial();



	/**
	Sets  the  output  baud rate, which must be one of these constants:
	B0, B50, B75, B110, B134, B150,B200, B300, B600, B1200, B1800, B2400,
	B4800, B9600, B19200, B38400, B57600, B115200, B230400
	*/
	void setBaudrate ( speed_t speed );

	/**
	 * Returns the current baudrate
	 */
	speed_t getBaudrate( void );

	/**
	 * Sends the given bytes on the serial line
	 */
	void send( const unsigned char);

	/** Opens the serial port
	 *
	 * @returns whether the port could be opened
	 */
	bool openPort( void );

private:
	string deviceName;
	int fd;
	termios options;
	speed_t baudrate;
};

#endif
