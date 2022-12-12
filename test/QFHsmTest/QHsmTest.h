#pragma once
#include "../../src/QF4CPlus/QActive.h"
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

	QFState m_sA;
	QFState m_sAA;
	QFState m_sAB;
	QFState m_sB;
	QFState m_sBA;
	QFState m_sBB;
protected:
	void InitializeStateMachine() override;

	//Q_STATE(QHsmTest, s0);
	Q_STATE_DECL(QHsmTest, sA);
	Q_STATE_DECL(QHsmTest, sAA);
	
	QFState sAA_call(shared_ptr<IQFEvent> qEvent);
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

