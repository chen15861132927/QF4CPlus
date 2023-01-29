#pragma once
#include "Interfaces/IQActive.h"
#include "Interfaces/IQFEvent.h"
#include "Interfaces/IQHsm.h"
#include "QFEvent.h"
#include "QHsm.h"
#include "Interfaces/IQEventQueue.h"
#include <QThread>
#include <qDebug>

namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QActive :public QHsm,public QThread ,public IQActive
	{
	private:
		shared_ptr<IQEventQueue> m_EventQueue;
		int m_index;
		bool m_isRunning;

	public:
		QActive();
		~QActive();
		int getPriority();

		void start(int index);

		void postFIFO(shared_ptr<IQFEvent> qEvent);

		void postLIFO(shared_ptr<IQFEvent> qEvent);
 
	protected:
 		void run() override;
	};
}