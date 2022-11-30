#include "QActive.h"
#include "QEventQueue.h"
using namespace QtQf4CPlus;

QActive::QActive()
{
	m_EventQueue = make_shared<QEventQueue>();
	//m_ExecutionThread = make_shared<IRegularThread>(this);
}
QActive::~QActive()
{
}
int QActive::GetPriority()
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
	m_index = index;
	QThread::start();
}
void QActive::PostFIFO(shared_ptr<IQEvent> qEvent)
{
	m_EventQueue->EnqueueFIFO(qEvent);

}
void QActive::PostLIFO(shared_ptr<IQEvent> qEvent)
{
	m_EventQueue->EnqueueLIFO(qEvent);
}

//shared_ptr<IRegularThread> QFActive::getQThread()
//{
//	return m_ExecutionThread;
//}

//shared_ptr<IQEvent> QActive::DeQueue()
//{
//	return m_EventQueue->DeQueue();
//}
void QActive::run()
{
	this->m_isRunning = true;
	Init();

	// event-loop
	while (true)
	{
		// for-ever
		shared_ptr<IQEvent> iQEvent = m_EventQueue->DeQueue();
		if (iQEvent->signal() != QSignals::Terminate)
		{
			qDebug() << "CurrentStateName" << getCurrentStateName() << "---" << iQEvent->ToString();
			Dispatch(iQEvent);
			continue;
		}
		break;
		m_isRunning = false;
	}
}
