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

}

QHsmTest::~QHsmTest()
{
}

void QHsmTest::InitializeStateMachine()
{
	QF::getInstance()->Subscribe(shared_from_this(), MyQSignals::E1_Sig);
	QF::getInstance()->Subscribe(shared_from_this(), MyQSignals::E2_Sig);
	QF::getInstance()->Subscribe(shared_from_this(), MyQSignals::E3_Sig);
	QF::getInstance()->Subscribe(shared_from_this(), MyQSignals::E4_Sig);
	QF::getInstance()->Subscribe(shared_from_this(), MyQSignals::E5_Sig);
	QF::getInstance()->Subscribe(shared_from_this(), MyQSignals::E6_Sig);
	qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "top-INIT;" << endl;

	InitializeState(m_sA); // initial transition			
}

QString QHsmTest::sA(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sA-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sA-EXIT;" << endl;
		//return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E4_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sA-E4_Sig;" << endl;
		TransitionTo(m_sB);
		return nullptr;;
	}
	else if (qEvent->signal() == QSignals::Init)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sA-INIT;" << endl;
		InitializeState(m_sAA);
		return nullptr;
	}

	return this->TopState;
}
QString QHsmTest::sAA(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAA-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAA-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E1_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAA-E1_Sig;" << endl;
		TransitionTo(m_sAB);
		return nullptr;
	}

	return m_sA;
}


QString QHsmTest::sAB (shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAB-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAB-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E2_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAB-E2_Sig;" << endl;
		TransitionTo(m_sAA, s_Tran_sAB_sAA);
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E3_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sAB-E3_Sig;" << endl;
		TransitionTo(m_sBB/*, s_Tran_sAB_sBB*/);
		return nullptr;
	}
	return m_sA;
}

QString QHsmTest::sB (shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sB-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sB-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Init)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sB-INIT;" << endl;
		InitializeState(m_sBA);
		return nullptr;
	}

	return this->TopState;
}
QString QHsmTest::sBA(shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBA-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBA-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E1_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBA-E1_Sig;" << endl;
		TransitionTo(m_sBB, s_Tran_sBA_sBB);
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E2_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBA-E2_Sig;" << endl;
		TransitionTo(m_sA/*, s_Tran_sBA_sA*/);
		return nullptr;
	}
	return m_sB;
}
QString QHsmTest::sBB (shared_ptr<IQFEvent> qEvent)
{
	if (qEvent->signal() == QSignals::Entry)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBB-ENTRY;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == QSignals::Exit)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBB-EXIT;" << endl;
		return nullptr;
	}
	else if (qEvent->signal() == MyQSignals::E2_Sig)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName() << "sBB-E2_Sig;" << endl;
		TransitionTo(m_sBA/*, s_Tran_sBB_sBA*/);
		return nullptr;
	}

	return m_sB;
}