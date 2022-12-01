#include "QFTimer.h"

using namespace QtQf4CPlus;

QFTimer::QFTimer(QActive* qActive)
{
	m_QActive = qActive;
}
QFTimer::~QFTimer()
{
}

void QFTimer::singleShot(int msec, shared_ptr<QEvent> qEvent)
{
	m_QEvent = qEvent;
	connect(&m_Timer, &QTimer::timeout, this, &QFTimer::onTimeOut);

	m_Timer.start(msec);
}

void QFTimer::stop()
{
	m_Timer.stop();
}

void QFTimer::onTimeOut()
{
	m_QActive->PostLIFO(m_QEvent);
}