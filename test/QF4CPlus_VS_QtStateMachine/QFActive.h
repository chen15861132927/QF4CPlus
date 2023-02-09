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
	/*const QString m_sTestState="sTestState";
	const QString m_sA="sA";
	const QString m_sB="sB";
	const QString m_sC="sC";
	const QString m_sD="sD";
	const QString m_sE="sE";
	const QString m_sF="sF";
	const QString m_sfinal = "sfinal";*/
protected:
	void InitializeStateMachine() override;
	Q_STATE_DECL(sTestState);
	Q_STATE_DECL(sA);
	Q_STATE_DECL(sB);
	Q_STATE_DECL(sC);
	Q_STATE_DECL(sD);
	Q_STATE_DECL(sE);
	Q_STATE_DECL(sF);
	Q_STATE_DECL(sfinal);


	//Q_INVOKABLE QString sTestState(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sA(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sB(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sC(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sD(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sE(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sF(shared_ptr<IQFEvent> qEvent);

	//Q_INVOKABLE QString sfinal(shared_ptr<IQFEvent> qEvent);


//shared_ptr<TransitionChain> s_Tran_sTestState_sA=nullptr;
//shared_ptr<TransitionChain> s_Tran_sA_sB=nullptr;
//shared_ptr<TransitionChain> s_Tran_sB_sC=nullptr;
//shared_ptr<TransitionChain> s_Tran_sC_sD=nullptr;
//shared_ptr<TransitionChain> s_Tran_sD_sE=nullptr;
//shared_ptr<TransitionChain> s_Tran_sE_sF=nullptr;
//shared_ptr<TransitionChain> s_Tran_sF_sA=nullptr;
//shared_ptr<TransitionChain> s_Tran_sF_sFinal = nullptr;


};

