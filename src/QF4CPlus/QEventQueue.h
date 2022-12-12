#pragma once
#include "Interfaces/IQEventQueue.h"
#include <QMutex>
#include <QWaitCondition>

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QEventQueue : public IQEventQueue
	{
	private:
		QList<shared_ptr<IQFEvent>> _mEventList;
		QMutex mutex;
		QWaitCondition eventIsEmpty;

	public:
		QEventQueue();
		~QEventQueue();
		bool IsEmpty();

		int Count();

		void EnqueueFIFO(shared_ptr<IQFEvent> qEvent);

		void EnqueueLIFO(shared_ptr<IQFEvent> qEvent);

		shared_ptr<IQFEvent> DeQueue();
		shared_ptr<IQFEvent> Peek();
	};

}