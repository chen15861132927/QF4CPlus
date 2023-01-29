#pragma once
#include "../QF4CPlus/QActive.h"
#include "qf4cplusequipment_global.h"

using namespace QtQf4CPlus;
class QF4CPLUSEQUIPMENT_EXPORT ActiveProcess : public QActive
{
public:
	static shared_ptr<QSignal> SigInitialized;  //= new Signal("Initialized");
	static shared_ptr<QSignal> SigStart;        //= new Signal("Start");
	static shared_ptr<QSignal> SigStop;         //= new Signal("Stop");
	static shared_ptr<QSignal> SigAbort;        //= new Signal("Abort");
	static shared_ptr<QSignal> SigPause;        //= new Signal("Pause");
	static shared_ptr<QSignal> SigResume;       //= new Signal("Resume");

	ActiveProcess()
	{
		//uniqueTraceName = QString("%1-%2").arg(base.ToString()).arg(this.GetHashCode());
	}

	ActiveProcess(string name)
	{
		//uniqueTraceName = QString.Format("{0}-{1}", base.ToString(), name);
	}
protected:
	const shared_ptr<QSignal> SigStateJob = std::make_shared<QSignal>("StateJob");
	const shared_ptr<QSignal> SigError = std::make_shared<QSignal>("Error");
	const shared_ptr<QSignal> SigRecover = std::make_shared<QSignal>("Recover");

	QList<shared_ptr<IQFEvent>> m_reminderSignals;
	QString uniqueTraceName = "";
	bool simulation;
	QFState targetState;
	QFState stateHistory;
	QFState stateRetry;



};
