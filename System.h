

#ifndef SYSTEM_H
#define SYSTEM_H

#include "MessageManager.h"

class MessageManager; // forward declaration
struct BasicMessage;

class System {
private:
	MessageManager* messenger;

public:
	System(MessageManager* messengerObject);
	virtual void update() = 0;
	virtual void receiveMessage(BasicMessage *message) = 0; // will need to use dynamic_cast to determine message type
};

#endif