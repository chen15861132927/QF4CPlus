#include "QEventQueue.h"
#include "QEvent.h"
using namespace QtQf4CPlus;

QEventQueue::QEventQueue()
{
}
QEventQueue::~QEventQueue()
{
}
bool QEventQueue::IsEmpty()
{
	bool isEmpty = false;
	mutex.lock();
	isEmpty = _mEventList.isEmpty();
	mutex.unlock();
	return isEmpty;
}

int QEventQueue::Count()
{
	int count = -99;
	mutex.lock();
	count = _mEventList.length();
	mutex.unlock();
	return count;
}

void QEventQueue::EnqueueFIFO(shared_ptr<IQEvent> qEvent)
{
	mutex.lock();
	_mEventList.push_back(qEvent);
	eventIsEmpty.wakeAll();
	mutex.unlock();
}

void QEventQueue::EnqueueLIFO(shared_ptr<IQEvent> qEvent)
{
	mutex.lock();
	_mEventList.push_front(qEvent);
	eventIsEmpty.wakeAll();
	mutex.unlock();
}

shared_ptr<IQEvent> QEventQueue::DeQueue()
{
	mutex.lock();
	if (_mEventList.isEmpty())
	{
		// We wait for the next event to be put into the queue
		eventIsEmpty.wait(&mutex);
	}
	auto res = _mEventList.takeFirst();
	mutex.unlock();
	return res;
}

shared_ptr<IQEvent>  QEventQueue::Peek()
{
	mutex.lock();
	if (_mEventList.isEmpty())
	{
		return nullptr;
	}
	else
	{
		return _mEventList.first();
	}
	mutex.unlock();
}