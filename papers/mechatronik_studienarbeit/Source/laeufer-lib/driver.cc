#include "driver.h"
#include "bus_manager.h"
#include "message_dispatcher.h"
#include "message.h"


driver::driver()
{
	idLocked=false;
	md=NULL;
}


void driver::setMessageDispatcher(message_dispatcher* M)
{
	md=M;
}


void driver::send(Message* m)
{
	if(m->getId()!=getID())
	{
		std::cerr << __FILE__<<": Message id not the same as driver id." << endl;
		if(m->isLocked())
		{
			std::cerr << __FILE__<<": Message locked. giving up." << endl;
			return;
		}
		std::cerr << __FILE__ << ": Setting driver id as message id." << endl;
		m->setId(getID());
	}

	//If we reached this line, everything went fine ;-)
	//lock the message.
	m->lock();

	//and put it on its way...
	md->send(m);
}//send();


void driver::send(int op)
{
	Message* m = new Message();
	m->setId(getID());
	m->setOp(op);
	send(m);
}


int driver::getID(void)
{
	return id;
}


void driver::setID(int ID)
{
	if(idLocked==true)
	{
		std::cerr << __FILE__ <<
			": Warning: Someone tried to change the id after it has been set once."
			<< endl;
		return;
	}
	idLocked=true;
	id=ID;
}
