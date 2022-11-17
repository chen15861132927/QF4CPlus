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
}
