#include "QFActive.h"
#include <qDebug>
#include <iostream>
#include "../../src/QF4CPlus/QF.h"
#include "QF4CPlus_VS_QtStateMachine.h"
shared_ptr<QSignal> QFActive::E1_Sig = std::make_shared<QSignal>("E1_Sig");

QFActive::QFActive()
{
	Q_SET(m_sTestState, sTestState);
	Q_SET(m_sA, sA);
	Q_SET(m_sB, sB);
	Q_SET(m_sC, sC);
	Q_SET(m_sD, sD);
	Q_SET(m_sE, sE);
	Q_SET(m_sF, sF);
	Q_SET(m_sfinal, sfinal);
}
QFActive::~QFActive()
{
}

void QFActive::InitializeStateMachine()
{
	finalTime = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
	InitializeState(m_sTestState); // initial transition			
}

Q_STATE_DEF(QFActive, sTestState)
{

	if (qEvent->signal() == QSignals::Init)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-INIT;" << endl;
		InitializeState(m_sA);
		return nullptr;
	}

	return this->TopState;
}

Q_STATE_DEF(QFActive, sA)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		if (count != 0)
		{
			finalTime = finalTime + std::chrono::high_resolution_clock::now() - startTime;
		}
		count++;
		return nullptr;
	}
	if (qEvent->signal() == Start_Sig)
	{
		startTime = std::chrono::high_resolution_clock::now();

		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-E4_Sig;" << endl;
		TransitionTo(m_sA);
		return nullptr;
	}

	return this->m_sTestState;
}

Q_STATE_DEF(QFActive, sB)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		TransitionTo(m_sC, s_Tran_sB_sC);
		return nullptr;
	}

	return this->m_sTestState;
}

Q_STATE_DEF(QFActive, sC)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		TransitionTo(m_sD, s_Tran_sC_sD);
		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sD)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		TransitionTo(m_sE, s_Tran_sD_sE);
		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sE)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		TransitionTo(m_sF, s_Tran_sE_sF);
		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sF)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		TransitionTo(m_sA, s_Tran_sF_sA);
		return nullptr;
	}

	return this->m_sTestState;
}Q_STATE_DEF(QFActive, sfinal)
{
	if (qEvent->signal() == E1_Sig)
	{
		TransitionTo(m_sA);
		return nullptr;
	}

	return this->m_sTestState;
}