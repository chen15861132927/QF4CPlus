#pragma once
#include <QThread>
#include "qf4cplus_global.h"
namespace QtQf4CPlus
{
	class QActive;

	class QF4CPLUS_EXPORT QActiveThread : public QThread
	{

	public:
		explicit QActiveThread(QActive*);
		~QActiveThread();
		void closeRun();
	protected:
		void run();
	private:
		bool m_isRunning=false;

		QActive* m_currentActive;
	};
}