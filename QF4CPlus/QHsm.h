#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QState.h"
#include "IQHsm.h"
#include "QEvent.h"
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QHsm :public IQHsm
	{
	public:
		QHsm();
		~QHsm();
		void Init();

	private:
		QState m_MyStateMethod;
		QState m_MySourceStateMethod;

		static shared_ptr<QState> _sTopState;

		static QState Top(shared_ptr<IQEvent> qEvent)
		{
			QState empty("Top");
			return empty;
		}

		QState GetSuperStateMethod(QState stateMethod);

		QState Trigger(QState stateMethod, shared_ptr<QSignal> qSignal);
		void ExitUpToSourceState();

	protected:

		void InitializeState(QState state);

		bool IsInState(QState inquiredState);

		void Dispatch(shared_ptr<IQEvent> qEvent);

		void DispatchSynchronized(shared_ptr<IQEvent> qEvent);

		QState TopState;

		void StateTrace(QState state, shared_ptr<QSignal> signal);
	};
};