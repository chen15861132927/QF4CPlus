#include "QFActive.h"
#include <qDebug>
#include <iostream>
#include "../../src/QF4CPlus/QF.h"
#include "QF4CPlus_VS_QtStateMachine.h"
shared_ptr<QSignal> QFActive::E1_Sig = std::make_shared<QSignal>("E1_Sig");
shared_ptr<QSignal> QFActive::SigStateJob = std::make_shared<QSignal>("SigStateJob");

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
		TransitionTo(m_sA);
		return nullptr;
	}

	return this->TopState;
}
//Q_STATE_DEF(QFActive, sA)
//{
//	//qDebug() << "sA-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;
//
//	if (qEvent->signal() == QSignals::Init)
//	{
//		//qDebug() << "sA-Entry;" << getCurrentStateName() << endl;
//
//		if (count != 0)
//		{
//			finalTime = finalTime + std::chrono::high_resolution_clock::now() - startTime;
//		}
//		count++;
//	}
//	if (qEvent->signal() == QSignals::Exit)
//	{
//		startTime = std::chrono::high_resolution_clock::now();
//	}
//	if (qEvent->signal() == Start_Sig)
//	{
//		//startTime = std::chrono::high_resolution_clock::now();
//
//		//qDebug() << "currentThreadId:" << QThread::currentThreadId() << "sA-E4_Sig;" << getCurrentStateName() << endl;
//		TransitionTo(m_sB);
//		postFIFO(std::make_shared<QFEvent>(SigStateJob));
//		return nullptr;
//	}
//
//	return this->m_sTestState;
//}
Q_STATE_DEF(QFActive, sA)
{
	//qDebug() << "sA-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateJob)
	{
		//qDebug() << "sA-Entry;" << getCurrentStateName() << endl;

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

		//qDebug() << "currentThreadId:" << QThread::currentThreadId() << "sA-E4_Sig;" << getCurrentStateName() << endl;
		TransitionTo(m_sB);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));
		return nullptr;
	}

	return this->m_sTestState;
}

Q_STATE_DEF(QFActive, sB)
{
	//qDebug() << "sB-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateJob)
	{
		//qDebug() <<"sB-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sC);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));

		return nullptr;
	}

	return this->m_sTestState;
}

Q_STATE_DEF(QFActive, sC)
{
	//qDebug() << "sC-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateJob)
	{
		//qDebug() << "sC-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sD);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));

		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sD)
{
	//qDebug() << "sD-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateJob)
	{
		//qDebug() << "sD-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sE);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));

		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sE)
{
	//qDebug() << "sE-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateJob)
	{
		//qDebug() << "sE-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sF);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));

		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sF)
{
	//qDebug() << "sF-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateJob)
	{
		//qDebug() << "sF-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sA);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));

		return nullptr;
	}

	return this->m_sTestState;
}
Q_STATE_DEF(QFActive, sfinal)
{
	if (qEvent->signal() == E1_Sig)
	{
		//qDebug() << "sfinal-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sA);
		return nullptr;
	}

	return this->m_sTestState;
}