#ifndef _debugTreiberGUIimpl_h
#define _debugTreiberGUIimpl_h
#include "debugTreiberGUI.h"
#include <vector>
class message_dispatcher;
class debug_driver;
class Message;

class DebugTreiberGUIimpl:public DebugTreiberGUI
{
  Q_OBJECT
	
 public:
  DebugTreiberGUIimpl( QWidget* parent = 0, const char* name = 0,
					   WFlags fl = 0);
  ~DebugTreiberGUIimpl(void);
  
 public slots:
	void newMessage(void);
    void send(void);
	void setNumberOfDataBytes(int x);
	void setID(int x);
	void showReceivedWithNumber(int x);
	void quit(void);
	
 private:
	message_dispatcher *md;
	debug_driver* treiber;
	std::vector<QSpinBox*> bytes;
	std::vector<QSpinBox*> rbytes;
	std::vector<Message> messages;
	int maximumBytes;
};
#endif







