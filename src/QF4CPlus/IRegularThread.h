#pragma once
#include <QThread>
 
#include "QHsm.h"
#include <qDebug>
class QFActive;
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IRegularThread : public QThread
	{
	public:
		IRegularThread(shared_ptr<QFActive> act);
		//............................................................................
		~IRegularThread();
		//............................................................................
		void run();

  
	private:
		shared_ptr<QFActive> m_act;
		bool  m_isRunning;
	};

}
