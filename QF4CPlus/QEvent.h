#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QSignal.h"
#include "IQEvent.h"
#include "QState.h"
#include <QPointer>
#include <QVariant>

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QEvent :public IQEvent
	{
		Q_OBJECT
	private:
		shared_ptr<QSignal> _signal;

		shared_ptr<QObject> _eventObject;

	public:
		const shared_ptr<QSignal> signal()
		{
			return _signal;
		}

		const shared_ptr<QObject> getEventObject()
		{
			return _eventObject;
		}

		QEvent(shared_ptr<QSignal> signal)
		{
			_signal = signal;
		}

		QEvent(shared_ptr<QSignal> signal, shared_ptr<QObject> eventObject)
		{
			_signal = signal;
			_eventObject = eventObject;
		}

		bool IsSignal(shared_ptr<QSignal> sig)
		{
			return sig == _signal;
		}

		QString ToString()
		{
			return _signal->ToString();
		}

		int GetHashCode()
		{
			return _signal->GetHashCode();
		}
	};
};
