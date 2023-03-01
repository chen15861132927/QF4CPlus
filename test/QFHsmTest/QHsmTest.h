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

class QHsmTest :public QActive
{
	Q_OBJECT;
public:
	QHsmTest();
	~QHsmTest();


protected:
	void InitializeStateMachine() override;
	Q_STATE_DECL(sA);
	Q_STATE_DECL(sAA);
	Q_STATE_DECL(sAB);
	Q_STATE_DECL(sB);
	Q_STATE_DECL(sBA);
	Q_STATE_DECL(sBB);


	static shared_ptr<TransitionChain> s_Tran_sAB_sAA;
	static shared_ptr<TransitionChain> s_Tran_sAB_sBB;
	static shared_ptr<TransitionChain> s_Tran_sBA_sBB;
	static shared_ptr<TransitionChain> s_Tran_sBA_sA;
	static shared_ptr<TransitionChain> s_Tran_sBB_sBA;
};

