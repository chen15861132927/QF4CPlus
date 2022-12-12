#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QSignal.h"
#include "Interfaces/IQFEvent.h"
#include "QState.h"
#include <QPointer>
#include <QVariant>

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QFEvent :public IQFEvent
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

		QFEvent(shared_ptr<QSignal> signal)
		{
			_signal = signal;
		}

		QFEvent(shared_ptr<QSignal> signal, shared_ptr<QObject> eventObject)
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
			return _signal->ToString()+ _signal->GetHashCode();
		}

		int GetHashCode()
		{
			return _signal->GetHashCode();
		}
	};
};
