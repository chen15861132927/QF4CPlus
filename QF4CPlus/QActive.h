#pragma once
#include "Interfaces/IQActive.h"
#include "Interfaces/IQEvent.h"
#include "Interfaces/IQHsm.h"
#include "QEvent.h"
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
		//shared_ptr<IRegularThread> m_ExecutionThread;
		bool  m_isRunning;

	public:
		QActive();
		~QActive();
		int GetPriority();

		void Start(int index);

		void PostFIFO(shared_ptr<IQEvent> qEvent);

		void PostLIFO(shared_ptr<IQEvent> qEvent);
 
		//shared_ptr<IRegularThread> getQThread();
		//shared_ptr<IQEvent> DeQueue();
	protected:
 		void run() override;
	};
}