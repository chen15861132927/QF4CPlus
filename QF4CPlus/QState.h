#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "IQEvent.h"
#include <functional>
#include <memory>

using namespace std;

namespace QtQf4CPlus
{
    typedef void* (*QStateBase)(void* const me, shared_ptr<IQEvent> qEvent);

    typedef QStateBase(*QState)(void* const me, shared_ptr<IQEvent> qEvent);

#define Q_STATE(subclass_, state_) \
    static QState state_(void* const me, shared_ptr<IQEvent> qEvent)\
	{ \
        return static_cast<subclass_ *>(me)->state_ ## _call(qEvent);\
	} \
    QState state_ ## _call(shared_ptr<IQEvent> qEvent)

#define Q_STATEFUN(subclass_, state_) \
    QState subclass_::state_ ## _call(shared_ptr<IQEvent> qEvent)
}
