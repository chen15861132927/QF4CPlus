#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "IQFEvent.h"
#include "QState.h"
//#include "IRegularThread.h"
#include "QHsm.h"
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQActive
	{
	public:
		virtual int GetPriority() = 0;

		virtual	void start(int priority) = 0;

		virtual void PostFIFO(shared_ptr<IQFEvent> qEvent) = 0;

		virtual	void PostLIFO(shared_ptr<IQFEvent> qEvent) = 0;
		 
		//virtual shared_ptr<IRegularThread> getQThread()=0;

		//virtual shared_ptr<IQFEvent> DeQueue()=0;
	};
}
