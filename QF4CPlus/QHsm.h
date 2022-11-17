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
		QState _mMyStateMethod;
		QState _mMySourceStateMethod;

		static QState _sTopState;

		static QState Top(shared_ptr<IQEvent> qEvent)
		{
			return nullptr;
		}

		QState GetSuperStateMethod(QState stateMethod);

		QState Trigger(QState stateMethod, shared_ptr<QSignal> qSignal);

	protected:

		void InitializeState(QState state);

		bool IsInState(QState inquiredState)
		{
			return true;
		}

		void Dispatch(shared_ptr<IQEvent> qEvent)
		{
		}

		void DispatchSynchronized(shared_ptr<IQEvent> qEvent)
		{
		}

		QState TopState;

		void StateTrace(QState state, shared_ptr<QSignal> signal)
		{
		}

	};
};