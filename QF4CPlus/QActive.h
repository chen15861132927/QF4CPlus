#pragma once
#include "Interfaces/IQActive.h"
#include "Interfaces/IQEvent.h"
#include "Interfaces/IQHsm.h"
#include "QEvent.h"
#include "QHsm.h"
namespace QtQf4CPlus
{
	class QActive :public QHsm, public IQActive
	{
	public:
		QActive();
		~QActive();
		int GetPriority();

		QString GetCurrentStateName();

		void Start(int priority);

		void PostFIFO(shared_ptr<IQEvent> qEvent);

		void PostLIFO(shared_ptr<IQEvent> qEvent);

		bool IsInState(QState inquiredState);
	};
}