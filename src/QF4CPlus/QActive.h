#pragma once
#include "Interfaces/IQActive.h"
#include "Interfaces/IQFEvent.h"
#include "Interfaces/IQHsm.h"
#include "QFEvent.h"
#include "QHsm.h"
#include "Interfaces/IQEventQueue.h"
#include <QThread>
#include <qDebug>
#include "QActiveThread.h"
namespace QtQf4CPlus
{
	class QActiveThread;
	class QF4CPLUS_EXPORT QActive :  public QHsm, public IQActive,public enable_shared_from_this<QActive>
	{
		Q_OBJECT
	private:
		shared_ptr<IQEventQueue> m_EventQueue;
		shared_ptr<QActiveThread> m_ExecutionThread;
		int m_index;
		friend class QActiveThread;  //���� CDriver Ϊ��Ԫ��

	public:
		QActive();
		~QActive();
		int getPriority();
		QString objectName() const;
		void setObjectName(const QString& name);
		void start(int index);

		void postFIFO(shared_ptr<IQFEvent> qEvent);

		void postLIFO(shared_ptr<IQFEvent> qEvent);

	protected:
		void Join()
		{
			if(m_ExecutionThread!=nullptr)
				m_ExecutionThread->wait();
		}
	};
	

	
}