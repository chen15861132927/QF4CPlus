#include "QActiveThread.h"
#include "QActive.h"
#include "QHsm.h"
using namespace QtQf4CPlus;


QActiveThread::QActiveThread(QActive* father)
{
	m_currentActive = father;
}
QActiveThread::~QActiveThread()
{
}
void QActiveThread::closeRun()
{
	this->m_isRunning = false;
}

void QActiveThread::run()
{
	this->m_isRunning = true;
	m_currentActive->Init();
	// event-loop
	while (m_isRunning)
	{
		// for-ever
		shared_ptr<IQFEvent> iQEvent = m_currentActive->m_EventQueue->DeQueue();
		if (iQEvent->signal() != QSignals::Terminate)
		{
			//qDebug() << "CurrentStateName" << m_currentActive->getCurrentStateName() << "---" << iQEvent->ToString();
			m_currentActive->Dispatch(iQEvent);
			continue;
		}
		break;
		m_isRunning = false;
	}
}