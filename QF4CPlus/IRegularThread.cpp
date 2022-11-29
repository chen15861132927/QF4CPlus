#pragma once
#include <QThread>

#include "QFActive.h"
#include "QHsm.h"
#include <qDebug>
using namespace QtQf4CPlus;

IRegularThread::IRegularThread(shared_ptr<QFActive> act)
	: m_act(act),
	m_isRunning(false)
{
}
//............................................................................
IRegularThread::~IRegularThread()
{
	wait();
}
//............................................................................
void IRegularThread::run()
{
	shared_ptr<IRegularThread> thread = m_act->getQThread();
	thread->m_isRunning = true;

	// event-loop
	while (true)
	{
		// for-ever
		shared_ptr<IQEvent> iQEvent = m_act->DeQueue();
		if (iQEvent != QSignals::Terminate)
		{
			qDebug() << "CurrentStateName" << m_act->getCurrentStateName() << "---" << iQEvent->ToString();
			m_act->Dispatch(iQEvent);
			continue;
		}
		break;
		thread->m_isRunning = false;
	}
}
