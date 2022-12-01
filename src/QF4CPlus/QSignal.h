#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include <memory>
using namespace std;
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QSignal :QObject
	{
		Q_OBJECT

	private:
		static int _maxSignalCount;

		int _signalValue;

		QString _signalName;

	public:

		QSignal(QString name);

		QString ToString();

		explicit operator int();
		bool operator ==(QSignal lhs);
		bool operator !=(QSignal lhs);

		int GetHashCode();

	};
 
};
