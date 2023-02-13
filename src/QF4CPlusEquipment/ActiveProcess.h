#pragma once
#include "EquipmentActiveBase.h"
#include "qf4cplusequipment_global.h"
#include <QThread>
#include "../QF4CPlus/QF.h"
using namespace QtQf4CPlus;
class QF4CPLUSEQUIPMENT_EXPORT ActiveProcess : public EquipmentActiveBase
{
	Q_OBJECT;

protected:
	Q_STATE_DECL(stateInit);
	Q_STATE_DECL(stateIdle);
	Q_STATE_DECL(stateIdleWithError);
	Q_STATE_DECL(stateActive);
	Q_STATE_DECL(stateProcess);
	Q_STATE_DECL(stateRunInit);
	Q_STATE_DECL(stateRun);
	Q_STATE_DECL(statePaused);
	Q_STATE_DECL(stateError);
	Q_STATE_DECL(statePause);
	Q_STATE_DECL(stateAborting);
	Q_STATE_DECL(stateStopping);


};
