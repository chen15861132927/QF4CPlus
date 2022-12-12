#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "Interfaces/IQActive.h"
#include "Interfaces/IQF.h"
#include "QActive.h"
#include <QMap>
#include <QMutex>
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QF :public IQF
	{
	private:
		QF();
		~QF();
	  static QF* qinstance;
	  QMutex mutex;

	  QHash<int, QHash<int, QActive*>> _mSignalSubscribers;
	public:
 
		static QF* getInstance();
		void Initialize(int maxSignal);

		void Subscribe(QActive* qActive, shared_ptr<QSignal> qSignal);

		void Unsubscribe(QActive* qActive, shared_ptr<QSignal> qSignal);

		void Publish(shared_ptr<QFEvent> qEvent);
	};
};
