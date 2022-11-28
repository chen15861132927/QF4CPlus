#pragma once
#include <QThread>
#include "Interfaces/IQActive.h"
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IRegularThread : public QThread
	{

	public:
		AOThread(shared_ptr<IQActive> act)
			: m_act(act),
			m_isRunning(false)
		{
		}
		virtual ~AOThread() = 0;
		virtual void run() = 0;

	public:
		shared_ptr<IQActive> m_act;
		bool  m_isRunning;
	};

}
