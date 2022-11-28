#pragma once
#include "Interfaces/IQEventQueue.h"
#include <QMutex>
#include <QWaitCondition>

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QEventQueue : public IQEventQueue
	{
	private:
		QList<shared_ptr<IQEvent>> _mEventList;
		QMutex mutex;
		QWaitCondition eventIsEmpty;

	public:
		QEventQueue();
		~QEventQueue();
		bool IsEmpty();

		int Count();

		void EnqueueFIFO(shared_ptr<IQEvent> qEvent);

		void EnqueueLIFO(shared_ptr<IQEvent> qEvent);

		shared_ptr<IQEvent> DeQueue();
		shared_ptr<IQEvent> Peek();
	};

}