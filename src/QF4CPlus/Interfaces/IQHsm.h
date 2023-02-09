#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include <memory>
#include "IQFEvent.h"
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT IQHsm
	{
		
	public:
		virtual void Init() = 0;

		virtual bool IsInState(QString inquiredState) = 0;

		virtual void InitializeStateMachine() = 0;
		virtual void Dispatch(std::shared_ptr<IQFEvent> qEvent) = 0;

		virtual void DispatchSynchronized(std::shared_ptr<IQFEvent> qEvent) = 0;
	};
};
