#pragma once
#include "../QF4CPlus/QActive.h"
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



class QHsmTest :	public QActive
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
	Q_STATE_DECL(QHsmTest, sA);
	Q_STATE_DECL(QHsmTest, sAA);
	
	QState sAA_call(shared_ptr<IQEvent> qEvent);
	Q_STATE_DECL(QHsmTest, sAB);
	Q_STATE_DECL(QHsmTest, sB);
	Q_STATE_DECL(QHsmTest, sBA);
	Q_STATE_DECL(QHsmTest, sBB);


	static shared_ptr<TransitionChain> s_Tran_sAB_sAA;
	static shared_ptr<TransitionChain> s_Tran_sAB_sBB;
	static shared_ptr<TransitionChain> s_Tran_sBA_sBB;
	static shared_ptr<TransitionChain> s_Tran_sBA_sA;
	static shared_ptr<TransitionChain> s_Tran_sBB_sBA;
};

