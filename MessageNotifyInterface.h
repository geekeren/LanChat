#pragma once
#include "message.h"
class MessageNotifyInterface
{
public:

	MessageNotifyInterface()
	{
	}

	virtual ~MessageNotifyInterface()
	{
	}
	virtual void handleMessage(message)=0;
};

