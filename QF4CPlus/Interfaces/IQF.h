#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "IQActive.h"

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQF
	{
	public:
		virtual	void Initialize(int maxSignal) = 0;

		virtual	void Subscribe(IQActive qActive, Signal qSignal) = 0;

		virtual	void Unsubscribe(IQActive qActive, Signal qSignal) = 0;

		virtual	void Publish(QEvent qEvent) = 0;
	};
};
