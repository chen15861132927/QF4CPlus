#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QState.h"

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQHsm
	{
		
	public:
		virtual void Init() = 0;

		virtual bool IsInState(QState inquiredState) = 0;

		virtual void InitializeStateMachine() = 0;
		virtual void Dispatch(shared_ptr<IQEvent> qEvent) = 0;

		virtual void DispatchSynchronized(shared_ptr<IQEvent> qEvent) = 0;
	};
};
