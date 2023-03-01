#pragma once
#include <QString>
#include <memory>
#include "qf4cplus_global.h"
#include <QObject>
#include "QSignal.h"
#include "QSignals.h"
using namespace std;
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQFEvent:public QObject
	{
		Q_OBJECT
	public:
		virtual const shared_ptr<QSignal> signal() =0;

		virtual QString ToString() = 0;

		virtual bool IsSignal(shared_ptr<QSignal> sig) = 0;

	};
}
