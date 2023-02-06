#include "QActiveThread.h"
#include "QActive.h"
#include "QEventQueue.h"

using namespace QtQf4CPlus;

QActive::QActive()
{
	m_EventQueue = make_shared<QEventQueue>();
	m_ExecutionThread = make_shared<QActiveThread>(this);
}
QActive::~QActive()
{
	m_ExecutionThread->closeRun();
	m_EventQueue->EnqueueLIFO(make_shared<QFEvent>(QSignals::Terminate));
	m_ExecutionThread->wait();
}
int QActive::getPriority()
{
	return m_index;
}

void QActive::start(int index)
{
	/*if (m_ExecutionThread != nullptr)
	{
		throw exception("This active object is already started. The Start method can only be invoked once.");
	}*/
	if (index < 0)
	{
		throw new exception("The priority of an Active Object cannot be negative,priority");
	}	
	//setStackSize(102400000);
	m_index = index;
	m_ExecutionThread->start();
}
void QActive::postFIFO(shared_ptr<IQFEvent> qEvent)
{
	m_EventQueue->EnqueueFIFO(qEvent);

}
void QActive::postLIFO(shared_ptr<IQFEvent> qEvent)
{
	m_EventQueue->EnqueueLIFO(qEvent);
}

