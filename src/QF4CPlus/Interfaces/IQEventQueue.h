#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "IQFEvent.h"

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQEventQueue
	{
	public:
		virtual bool IsEmpty()=0;

		virtual int Count()=0;

		virtual	void EnqueueFIFO(shared_ptr<IQFEvent> qEvent) = 0;

		virtual	void EnqueueLIFO(shared_ptr<IQFEvent> qEvent) = 0;

		virtual	shared_ptr<IQFEvent> DeQueue() = 0;

		virtual	shared_ptr<IQFEvent> Peek() = 0;
	};
};