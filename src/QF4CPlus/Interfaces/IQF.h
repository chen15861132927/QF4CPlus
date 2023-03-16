#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "../QActive.h"

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQF
	{
	public:
		virtual	void Initialize(int maxSignal) = 0;

		virtual	void Subscribe(std::shared_ptr<QActive> qActive, shared_ptr<QSignal> qSignal) = 0;

		virtual	void Unsubscribe(std::shared_ptr<QActive> qActive, shared_ptr<QSignal> qSignal) = 0;

		virtual void Publish(shared_ptr<QFEvent> qEvent)=0;
	};
};
