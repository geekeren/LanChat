#pragma once
#include "message.h"
class ServiceDiscoverInterface
{
public:

	ServiceDiscoverInterface()
	{
	}

	~ServiceDiscoverInterface()
	{
	}

	virtual void handleServiceDiscoverMsg(Message msg)=0;

};

