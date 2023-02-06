#pragma once
#include "../../src/QF4CPlus/QActive.h"
using namespace QtQf4CPlus;
class QFActive:public QActive
{
	 Q_OBJECT
	 static shared_ptr<QSignal>  E1_Sig;
	 static shared_ptr<QSignal>  SigStateJob;

	 
public:
	QFActive();
	~QFActive();

	int getCurrentCount()
	{
		return count;
	}

	std::chrono::nanoseconds finalTime;
	shared_ptr<QSignal> Start_Sig = std::make_shared<QSignal>("Start_Sig");
	shared_ptr<QSignal> End_Sig = std::make_shared<QSignal>("End_Sig");

private:
	int count = 0;
	std::chrono::steady_clock::time_point startTime;
	QFState m_sTestState;
	QFState m_sA;
	QFState m_sB;
	QFState m_sC;
	QFState m_sD;
	QFState m_sE;
	QFState m_sF;
	QFState m_sfinal;
protected:
	void InitializeStateMachine() override;

	Q_STATE_DECL(QFActive, sTestState);
	Q_STATE_DECL(QFActive, sA);
	Q_STATE_DECL(QFActive, sB);
	Q_STATE_DECL(QFActive, sC);
	Q_STATE_DECL(QFActive, sD);
	Q_STATE_DECL(QFActive, sE);
	Q_STATE_DECL(QFActive, sF);
	Q_STATE_DECL(QFActive, sfinal);


//shared_ptr<TransitionChain> s_Tran_sTestState_sA=nullptr;
//shared_ptr<TransitionChain> s_Tran_sA_sB=nullptr;
//shared_ptr<TransitionChain> s_Tran_sB_sC=nullptr;
//shared_ptr<TransitionChain> s_Tran_sC_sD=nullptr;
//shared_ptr<TransitionChain> s_Tran_sD_sE=nullptr;
//shared_ptr<TransitionChain> s_Tran_sE_sF=nullptr;
//shared_ptr<TransitionChain> s_Tran_sF_sA=nullptr;
//shared_ptr<TransitionChain> s_Tran_sF_sFinal = nullptr;


};

