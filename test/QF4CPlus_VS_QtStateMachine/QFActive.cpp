#include "QFActive.h"
#include <qDebug>
#include <iostream>
#include "../../src/QF4CPlus/QF.h"
#include "QF4CPlus_VS_QtStateMachine.h"
shared_ptr<QSignal> QFActive::E1_Sig = std::make_shared<QSignal>("E1_Sig");
shared_ptr<QSignal> QFActive::SigStateRun = std::make_shared<QSignal>("SigStateJob");

QFActive::QFActive()
{

}
QFActive::~QFActive()
{
}

void QFActive::InitializeStateMachine()
{
	finalTime = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
	InitializeState(m_sTestState); // initial transition			
}
QString QFActive::sTestState(shared_ptr<IQFEvent> qEvent)
{

	if (qEvent->signal() == QSignals::Init)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-INIT;" << endl;
		TransitionTo(m_sA);
		return nullptr;
	}

	return this->TopState;
}
 
QString QFActive::sA(shared_ptr<IQFEvent> qEvent)
{
	//qDebug() << "sA-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateRun)
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
		postFIFO(std::make_shared<QFEvent>(SigStateRun));
		return nullptr;
	}

	return this->m_sTestState;
}

QString QFActive::sB(shared_ptr<IQFEvent> qEvent)
{
	//qDebug() << "sB-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateRun)
	{
		//qDebug() <<"sB-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sC);
		postFIFO(std::make_shared<QFEvent>(SigStateRun));

		return nullptr;
	}

	return this->m_sTestState;
}

QString QFActive::sC(shared_ptr<IQFEvent> qEvent)
{
	//qDebug() << "sC-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateRun)
	{
		//qDebug() << "sC-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sD);
		postFIFO(std::make_shared<QFEvent>(SigStateRun));

		return nullptr;
	}

	return this->m_sTestState;
}
QString QFActive::sD(shared_ptr<IQFEvent> qEvent)
{
	//qDebug() << "sD-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateRun)
	{
		//qDebug() << "sD-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sE);
		postFIFO(std::make_shared<QFEvent>(SigStateRun));

		return nullptr;
	}

	return this->m_sTestState;
}
QString QFActive::sE(shared_ptr<IQFEvent> qEvent)
{
	//qDebug() << "sE-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateRun)
	{
		//qDebug() << "sE-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sF);
		postFIFO(std::make_shared<QFEvent>(SigStateRun));

		return nullptr;
	}

	return this->m_sTestState;
}
QString QFActive::sF(shared_ptr<IQFEvent> qEvent)
{
	//qDebug() << "sF-;" << getCurrentStateName() << qEvent->signal()->ToString() << endl;

	if (qEvent->signal() == SigStateRun)
	{
		//qDebug() << "sF-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sA);
		postFIFO(std::make_shared<QFEvent>(SigStateRun));

		return nullptr;
	}

	return this->m_sTestState;
}

QString QFActive::sfinal(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == E1_Sig)
	{
		//qDebug() << "sfinal-Entry;" << getCurrentStateName() << endl;

		TransitionTo(m_sA);
		return nullptr;
	}

	return this->m_sTestState;
}