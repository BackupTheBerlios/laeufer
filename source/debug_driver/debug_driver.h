#ifndef _debug_driver_h
#define _debug_driver_h
#include "driver.h"
#include "debugTreiberGUIimpl.h"
class DebugTreiberGUIimpl;
/**
* @ short Driver used by debug-GUI
*/
class debug_driver: public driver
{
	Q_OBJECT

public:
	/**
	 * initialize the debugDriver
	 *
	 * @param id The id of the driver
	 */
	debug_driver(int id);

	virtual bool receive(message* m);
	virtual bool valid_command(int op);
	message* getLastMessage(void);

private:
	message* lastMessage;

signals:
	 void messageReceived(void);
};
#endif
