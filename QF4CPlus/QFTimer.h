#pragma once
#include <QTimer>
#include "QActive.h"
#include <QObject>
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QFTimer : public QObject
	{
		Q_OBJECT

	private:
		QActive *m_QActive;

		QTimer m_Timer;

		shared_ptr<QEvent> m_QEvent;

	public:
		QFTimer(QActive* qActive);
		~QFTimer();

		void singleShot(int msec, shared_ptr<QEvent> qEvent);

		void stop();

		void onTimeOut();
	};
}
