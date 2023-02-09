#include "QHsmTest.h"
#include <qDebug>
#include <iostream>
#include "../../src/QF4CPlus/QF.h"
shared_ptr<QSignal> MyQSignals::E1_Sig = std::make_shared<QSignal>("E1_Sig");
shared_ptr<QSignal> MyQSignals::E2_Sig = std::make_shared<QSignal>("E2_Sig");
shared_ptr<QSignal> MyQSignals::E3_Sig = std::make_shared<QSignal>("E3_Sig");
shared_ptr<QSignal> MyQSignals::E4_Sig = std::make_shared<QSignal>("E4_Sig");
shared_ptr<QSignal> MyQSignals::E5_Sig = std::make_shared<QSignal>("E5_Sig");
shared_ptr<QSignal> MyQSignals::E6_Sig = std::make_shared<QSignal>("E6_Sig");
shared_ptr<TransitionChain> QHsmTest::s_Tran_sAB_sAA = nullptr;
shared_ptr<TransitionChain> QHsmTest::s_Tran_sAB_sBB = nullptr;
shared_ptr<TransitionChain> QHsmTest::s_Tran_sBA_sBB = nullptr;
shared_ptr<TransitionChain> QHsmTest::s_Tran_sBA_sA = nullptr;
shared_ptr<TransitionChain> QHsmTest::s_Tran_sBB_sBA = nullptr;
QHsmTest::QHsmTest()
{
	QF::getInstance()->Subscribe(this, MyQSignals::E1_Sig);
	QF::getInstance()->Subscribe(this, MyQSignals::E2_Sig);
	QF::getInstance()->Subscribe(this, MyQSignals::E3_Sig);
	QF::getInstance()->Subscribe(this, MyQSignals::E4_Sig);
	QF::getInstance()->Subscribe(this, MyQSignals::E5_Sig);
	QF::getInstance()->Subscribe(this, MyQSignals::E6_Sig);
}

QHsmTest::~QHsmTest()
{
}

void QHsmTest::InitializeStateMachine()
{
	cout << "currentThreadId:" << QThread::currentThreadId() << "top-INIT;" << endl;

	InitializeState(m_sA); // initial transition			
}

QString QHsmTest::sA(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-EXIT;" << endl;
		//return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E4_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-E4_Sig;" << endl;
		TransitionTo(m_sB);
		return nullptr;;
	}
	else if (qEvent->signal() == QSignals::Init)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sA-INIT;" << endl;
		InitializeState(m_sAA);
		return nullptr;
	}

	return this->TopState;
}
QString QHsmTest::sAA(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAA-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAA-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E1_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAA-E1_Sig;" << endl;
		TransitionTo(m_sAB);
		return nullptr;
	}

	return m_sA;
}


QString QHsmTest::sAB (shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAB-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAB-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E2_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAB-E2_Sig;" << endl;
		TransitionTo(m_sAA, s_Tran_sAB_sAA);
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E3_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sAB-E3_Sig;" << endl;
		TransitionTo(m_sBB/*, s_Tran_sAB_sBB*/);
		return nullptr;
	}
	return m_sA;
}

QString QHsmTest::sB (shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sB-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sB-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Init)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sB-INIT;" << endl;
		InitializeState(m_sBA);
		return nullptr;
	}

	return this->TopState;
}
QString QHsmTest::sBA(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBA-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBA-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E1_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBA-E1_Sig;" << endl;
		TransitionTo(m_sBB, s_Tran_sBA_sBB);
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E2_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBA-E2_Sig;" << endl;
		TransitionTo(m_sA/*, s_Tran_sBA_sA*/);
		return nullptr;
	}
	return m_sB;
}
QString QHsmTest::sBB (shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBB-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBB-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E2_Sig)
	{
		cout << "currentThreadId:" << QThread::currentThreadId() << "sBB-E2_Sig;" << endl;
		TransitionTo(m_sBA/*, s_Tran_sBB_sBA*/);
		return nullptr;
	}

	return m_sB;
}