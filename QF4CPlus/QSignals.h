#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include <memory>
#include "QSignal.h"
using namespace std;
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QSignals
	{
	public:
		static shared_ptr<QSignal> Empty;
		static shared_ptr<QSignal> Init ;
		static shared_ptr<QSignal> Entry ;
		static shared_ptr<QSignal> Exit ;
		static shared_ptr<QSignal> Terminate;
	};
};
