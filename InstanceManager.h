#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H
#include "ErrorHandler.h"
class InstanceManager
{
	public:
		static ErrorHandler* handler;
		static InstanceManager* single();
	protected:
		static InstanceManager* manager;
		InstanceManager();
};

#endif
