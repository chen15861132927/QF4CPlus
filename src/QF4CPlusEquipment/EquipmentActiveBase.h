#pragma once
#include "../QF4CPlus/QActive.h"
#include "qf4cplusequipment_global.h"
#include <QThread>
#include "../QF4CPlus/QF.h"
using namespace QtQf4CPlus;
class QF4CPLUSEQUIPMENT_EXPORT EquipmentActiveBase : public QActive
{
	Q_OBJECT;
public:
	static shared_ptr<QSignal> SigInitialized;  //= new Signal("Initialized");
	static shared_ptr<QSignal> SigStart;        //= new Signal("Start");
	static shared_ptr<QSignal> SigStop;         //= new Signal("Stop");
	static shared_ptr<QSignal> SigAbort;        //= new Signal("Abort");
	static shared_ptr<QSignal> SigPause;        //= new Signal("Pause");
	static shared_ptr<QSignal> SigResume;       //= new Signal("Resume");

	EquipmentActiveBase(QString name="")
	{
		uniqueTraceName = QString("%1-%2-%3").arg(this->metaObject()->className()).arg(name).arg(QString::number(reinterpret_cast<quintptr>(QThread::currentThreadId()), 16));
	}
protected:
	const shared_ptr<QSignal> SigStateJob = std::make_shared<QSignal>("StateJob");
	const shared_ptr<QSignal> SigError = std::make_shared<QSignal>("Error");
	const shared_ptr<QSignal> SigRecover = std::make_shared<QSignal>("Recover");
 

	QList<shared_ptr<IQFEvent>> m_reminderSignals;
	QString uniqueTraceName = "";
	bool simulation;
	QString targetState;
	QString stateHistory;
	QString stateRetry;
	virtual	void InitializeStateMachine() = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="targetState"></param>
	virtual void TransitionToWithoutJob(QString targetState)
	{
		targetState = targetState;
		QActive::TransitionTo(targetState);
	}

	void TransitionTo(QString targetState)
	{
		TransitionToWithoutJob(targetState);
		postFIFO(std::make_shared<QFEvent>(SigStateJob));
	}

	void AddDeferredSignal(shared_ptr<IQFEvent> qEvent)
	{
		// may have to change qEvent.Equal(xx) to ensure value equality
		if (!m_reminderSignals.contains(qEvent))
			m_reminderSignals.append(qEvent);
		//AddDeferredSignal(qEvent.QSignal);
	}
	bool RecallDeferredSignal(shared_ptr<IQFEvent> qEvent)
	{
		return RecallDeferredSignal(qEvent->signal());
	}

	bool RecallDeferredSignal(shared_ptr<QSignal> signal)
	{
		for(auto qEvent : m_reminderSignals)
		{
			if (qEvent->IsSignal(signal))
			{
				m_reminderSignals.removeOne(qEvent);
				postFIFO(qEvent);
				return true;
			}
		}

		return false;
	}

	void RemoveDeferredSignal(shared_ptr<QSignal> signal)
	{
		//if (reminderSignals.Contains(signal))
		//    reminderSignals.Remove(signal);
		for (auto qEvent : m_reminderSignals)
		{
			if (qEvent->IsSignal(signal))
			{
				m_reminderSignals.removeOne(qEvent);
				return;
			}
		}
	}

	bool CheckDeferredSignal(shared_ptr<IQFEvent> qEvent)
	{
		return CheckDeferredSignal(qEvent->signal());
	}

	bool CheckDeferredSignal(shared_ptr<QSignal> signal)
	{
		for (auto qEvent : m_reminderSignals)
		{
			if (qEvent->IsSignal(signal))
			{
				return true;
			}
		}
		return false;
		//return reminderSignals.Contains(signal);
	}

	void ClearDeferredSignals()
	{
		m_reminderSignals.clear();
	}
	void LogMessage(string stateName, shared_ptr<IQFEvent> qEvent)
	{
		//TODO::
	}  
	virtual void TransitionToErrorState(exception exception)
	{
		//errorMessage = null;
		//currentException = new Exception("Error in state = " + targetState.Method.Name, exception);
		//stateHistory = targetState;
		postFIFO(std::make_shared<QFEvent>(SigError));
	}

	//virtual void TransitionToErrorState(ButtonList buttonList, Exception exception)
	//{
	//	currentException = new Exception("Error in state = " + targetState.Method.Name, exception);
	//	errorMessage = new APErrorMessage(this, buttonList);
	//	errorMessage.Format(currentException);
	//	errorMessage.Priority = 1;
	//	stateHistory = targetState;
	//	postFIFO(std::make_shared<QFEvent>(SigError));
	//}

	//void CreateStandardErrorMessage(ButtonList buttonList, Exception exception)
	//{
	//	errorMessage = new APErrorMessage(this, buttonList);
	//	errorMessage.Format(exception.Message);
	//	errorMessage.Priority = 1;
	//}

	virtual void DefaultErrorHandler()
	{
		/*if (errorMessage == null)
		{
			var buttonList = new ButtonList(ParselErrorButtonList.Abort, ParselErrorButtonList.Retry);
			errorMessage = new APErrorMessage(this, buttonList);
			if (currentException != null)
				errorMessage.Format(currentException);
			errorMessage.Priority = 1;
		}

		Services.ServiceManager.ErrorHandler.RegisterMessage(errorMessage as IErrorMessage);*/
	}

	/*bool IsRetry(shared_ptr<IQFEvent> qEvent)
	{
		IQFEvent e = (IQFEvent)qEvent;
		if (e != null && e.EventObject != null)
		{
			return ((ParselErrorButton)e.EventObject == ParselErrorButtonList.Retry);
		}
		return false;
	}*/


public:
	bool getSimulation()
	{
		return m_Simulation;
	}
	void setSimulation(bool simulation)
	{
		m_Simulation = simulation;
	}

	QString getTraceName()
	{
		return uniqueTraceName;
	}

	void Terminate()
	{
		postLIFO(std::make_shared<QFEvent>(QSignals::Terminate));
		QThread::msleep(0);
		Join();
	}
	// Methods -------------------------------------------------------------
	QString toString()
	{
		//return base.ToString();
		return uniqueTraceName;
	}
private:
	bool m_Simulation;
};

