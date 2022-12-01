#include "QSignals.h"
#include "QSignal.h"

namespace QtQf4CPlus
{
	int QSignal::_maxSignalCount = 0;
	shared_ptr<QSignal> QSignals::Empty = std::make_shared<QSignal>("Empty");
	shared_ptr<QSignal> QSignals::Init = std::make_shared<QSignal>("Init");
	shared_ptr<QSignal> QSignals::Entry = std::make_shared<QSignal>("Entry");
	shared_ptr<QSignal> QSignals::Exit = std::make_shared<QSignal>("Exit");
	shared_ptr<QSignal> QSignals::Terminate = std::make_shared<QSignal>("Terminate");
	QSignal::QSignal(QString name)
	{
		_signalName = name;
		_signalValue = _maxSignalCount++;
	}


	QString QSignal::ToString()
	{
		return _signalName;
	}
	QSignal::operator int()
	{
		return this->_signalValue;
	}
	bool QSignal::operator ==(QSignal lhs)
	{
		return lhs._signalValue == this->_signalValue;

	}
	bool QSignal::operator !=(QSignal lhs)
	{
		return lhs._signalValue == this->_signalValue;
	}

	int QSignal::GetHashCode()
	{
		return _signalValue;
	}

}
