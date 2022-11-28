#pragma once
#include "Interfaces/IQEventQueue.h"
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QEventQueue : public IQEventQueue
	{
	public:
		bool IsEmpty();

		int Count();

		void EnqueueFIFO(shared_ptr<IQEvent> qEvent);

		void EnqueueLIFO(shared_ptr<IQEvent> qEvent);

		shared_ptr<IQEvent> DeQueue();
	};

}