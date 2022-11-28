#include "QEventQueue.h"
#include "QEvent.h"
using namespace QtQf4CPlus;
bool QEventQueue::IsEmpty()
{
	return true;
}

int QEventQueue::Count()
{
	return 0;
}

void QEventQueue::EnqueueFIFO(shared_ptr<IQEvent> qEvent)
{
}

void QEventQueue::EnqueueLIFO(shared_ptr<IQEvent> qEvent)
{
}

shared_ptr<IQEvent> QEventQueue::DeQueue()
{
	return nullptr;
}