#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QSignal.h"
#include "QF.h"
#include "Interfaces/IQActive.h"

using namespace QtQf4CPlus;
QF* QF::qinstance = new QF;

QF* QF::getInstance()
{
	return QF::qinstance;
}
QF::QF()
{
}
QF::~QF()
{
}

void QF::Initialize(int maxSignal)
{
	for (int i = 0; i < maxSignal; i++)
	{
		_mSignalSubscribers.insert(i, QHash<int, QActive*>());
	}
}

void QF::Subscribe(QActive* qActive, shared_ptr<QSignal> qSignal)
{
	mutex.lock();
	auto findsignals = _mSignalSubscribers.find(qSignal->GetHashCode());
	if (findsignals == _mSignalSubscribers.end())
	{
		// this is the first time that somebody subscribes for this signal
		_mSignalSubscribers.insert(qSignal->GetHashCode(), QHash<int, QActive*>());
		findsignals = _mSignalSubscribers.find(qSignal->GetHashCode());
	}

	findsignals->insert(qActive->priority(), qActive);
	mutex.unlock();
}
void QF::Unsubscribe(QActive* qActive, shared_ptr<QSignal> qSignal)
{
	mutex.lock();
	auto findsignals = _mSignalSubscribers.find(qSignal->GetHashCode());
	if (findsignals != _mSignalSubscribers.end())
	{
		findsignals->remove(qActive->priority());
	}

	mutex.unlock();
}

void QF::Publish(shared_ptr<QFEvent> qEvent)
{
	mutex.lock();
	auto findsignals = _mSignalSubscribers.find(qEvent->signal()->GetHashCode());
	if (findsignals != _mSignalSubscribers.end())
	{
		// For simplicity we do not use the event propagae pattern that Miro Samek uses in his implementation.
		// This has two consequences:
		// a) We rely on the Garbage Collector to clean up events that are no longer used
		// b) We don't have the restriction that only once instance of a given type (signal value) can be in use at any given time
		for (auto iter = findsignals->begin(); iter != findsignals->end(); iter++)
		{
			iter.value()->PostFIFO(qEvent);
		}
	}

	mutex.unlock();
}


