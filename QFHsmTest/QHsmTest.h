#pragma once
#include "../QF4CPlus/QHsm.h"
using namespace QtQf4CPlus;
class MyQSignals
{
public:
	static shared_ptr<QSignal>  E1_Sig;
	static shared_ptr<QSignal>  E2_Sig;
	static shared_ptr<QSignal>  E3_Sig;
	static shared_ptr<QSignal>  E4_Sig;
	static shared_ptr<QSignal>  E5_Sig;
	static shared_ptr<QSignal>  E6_Sig;
	static shared_ptr<QSignal>  G_Sig;
	static shared_ptr<QSignal>  H_Sig;
};



class QHsmTest :
	public QHsm
{
public:
	QHsmTest();
	~QHsmTest();

private:

	QState m_sA;
	QState m_sAA;
	QState m_sAB;
	QState m_sB;
	QState m_sBA;
	QState m_sBB;
protected:
	void InitializeStateMachine() override;

	//Q_STATE(QHsmTest, s0);
	Q_STATE(QHsmTest, sA);
	//Q_STATE(QHsmTest, sAA);
	static QState sAA(void* const me, shared_ptr<IQEvent> qEvent)
	{
		QState temp = static_cast<QHsmTest*>(me)->sAA_call(qEvent);
		return temp;
	}
	QState sAA_call(shared_ptr<IQEvent> qEvent);
	Q_STATE(QHsmTest, sAB);
	Q_STATE(QHsmTest, sB);
	Q_STATE(QHsmTest, sBA);
	Q_STATE(QHsmTest, sBB);


	static shared_ptr<TransitionChain> s_Tran_sAB_sAA;
	static shared_ptr<TransitionChain> s_Tran_sAB_sBB;
	static shared_ptr<TransitionChain> s_Tran_sBA_sBB;
	static shared_ptr<TransitionChain> s_Tran_sBA_sA;
	static shared_ptr<TransitionChain> s_Tran_sBB_sBA;
};

