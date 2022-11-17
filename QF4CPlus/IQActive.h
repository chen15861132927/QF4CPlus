#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "IQEvent.h"
#include "QState.h"

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQActive
	{
	public:
		virtual int GetPriority() = 0;

		virtual QString GetCurrentStateName() = 0;

		virtual	void Start(int priority) = 0;

		virtual void PostFIFO(IQEvent qEvent) = 0;

		virtual	void PostLIFO(IQEvent qEvent) = 0;

		virtual	bool IsInState(QState inquiredState) = 0;
	};
};
