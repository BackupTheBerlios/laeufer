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

	virtual bool receive(Message* m);
	virtual bool valid_command(int op);
	Message* getLastMessage(void);

private:
	Message* lastMessage;

signals:
	 void messageReceived(void);
};
#endif
