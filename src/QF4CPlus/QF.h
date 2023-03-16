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

	  QHash<int, QHash<int, std::shared_ptr<QActive>>> _mSignalSubscribers;
	public:
 
		static QF* getInstance();
		void Initialize(int maxSignal);

		void Subscribe(std::shared_ptr<QActive> qActive, shared_ptr<QSignal> qSignal);

		void Unsubscribe(std::shared_ptr<QActive> qActive, shared_ptr<QSignal> qSignal);

		void Publish(shared_ptr<QFEvent> qEvent);
	};
};
