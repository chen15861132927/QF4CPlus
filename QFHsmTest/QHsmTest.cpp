#include "QHsmTest.h"
#include <qDebug>
#include <iostream>
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
	Q_SET(m_sA, sA);
	Q_SET(m_sAA, sAA);
	Q_SET(m_sAB, sAB);
	Q_SET(m_sB, sB);
	Q_SET(m_sBA, sBA);
	Q_SET(m_sBB, sBB);
}

QHsmTest::~QHsmTest()
{
}

void QHsmTest::InitializeStateMachine()
{
	cout << "top-INIT;";

	InitializeState(m_sA); // initial transition			
}

Q_STATEFUN(QHsmTest, sA)
{
	if (qEvent->getQSignal() == QSignals::Entry)
	{
		cout << "sA-ENTRY;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Exit)
	{
		cout << "sA-EXIT;";
		return nullptr;;
	}
	else if (qEvent->getQSignal() == MyQSignals::E4_Sig)
	{
		cout << "sA-E4_Sig;";
		TransitionTo(m_sB);
		return nullptr;;
	}
	else if (qEvent->getQSignal() == QSignals::Init)
	{
		cout << "sA-INIT;";
		InitializeState(m_sAA);
		return nullptr;
	}

	return this->TopState;
}

QState QHsmTest::sAA_call(shared_ptr<IQEvent> qEvent)
{
	if (qEvent->getQSignal() == QSignals::Entry)
	{
		cout << "sAA-ENTRY;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Exit)
	{
		cout << "sAA-EXIT;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == MyQSignals::E1_Sig)
	{
		cout << "sAA-E1_Sig;";
		TransitionTo(m_sAB);
		return nullptr;
	}

	return m_sA;
}



Q_STATEFUN(QHsmTest, sAB)
{
	if (qEvent->getQSignal() == QSignals::Entry)
	{
		cout << "sAB-ENTRY;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Exit)
	{
		cout << "sAB-EXIT;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == MyQSignals::E2_Sig)
	{
		cout << "sAB-E2_Sig;";
		TransitionTo(m_sAA, s_Tran_sAB_sAA);
		return nullptr;
	}
	else if (qEvent->getQSignal() == MyQSignals::E3_Sig)
	{
		cout << "sAB-E3_Sig;";
		TransitionTo(m_sBB, s_Tran_sAB_sBB);
		return nullptr;
	}
	return m_sA;
}

//private static TransitionChain s_Tran_s2_s1;
//private static TransitionChain s_Tran_s2_s11;
Q_STATEFUN(QHsmTest, sB)
{
	if (qEvent->getQSignal() == QSignals::Entry)
	{
		cout << "sB-ENTRY;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Exit)
	{
		cout << "sB-EXIT;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Init)
	{
		cout << "sB-INIT;";
		InitializeState(m_sBA);
		return nullptr;
	}

	return this->TopState;
}

Q_STATEFUN(QHsmTest, sBA)

{
	if (qEvent->getQSignal() == QSignals::Entry)
	{
		cout << "sBA-ENTRY;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Exit)
	{
		cout << "sBA-EXIT;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == MyQSignals::E1_Sig)
	{
		cout << "sBA-E1_Sig;";
		TransitionTo(m_sBB, s_Tran_sBA_sBB);
		return nullptr;
	}
	else if (qEvent->getQSignal() == MyQSignals::E2_Sig)
	{
		cout << "sBA-E2_Sig;";
		TransitionTo(m_sA, s_Tran_sBA_sA);
		return nullptr;
	}
	return m_sB;
}

Q_STATEFUN(QHsmTest, sBB)

{
	if (qEvent->getQSignal() == QSignals::Entry)
	{
		cout << "sBB-ENTRY;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == QSignals::Exit)
	{
		cout << "sBB-EXIT;";
		return nullptr;
	}
	else if (qEvent->getQSignal() == MyQSignals::E2_Sig)
	{
		cout << "sBB-E2_Sig;";
		TransitionTo(m_sBA, s_Tran_sBB_sBA);
		return nullptr;
	}

	return m_sB;
}