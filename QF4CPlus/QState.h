#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "Interfaces/IQEvent.h"
#include <functional>
#include <memory>

using namespace std;

namespace QtQf4CPlus
{
	typedef void* (*QStateBase)(void* const me, shared_ptr<IQEvent> qEvent);

	struct QState :QObject
	{
		QStateBase QStateFun;
		QString Name;
		QState(const QState& b)
		{
			QStateFun = b.QStateFun;
			Name = b.Name;
		}
		QState()
		{
			QStateFun = nullptr;
			Name = nullptr;
		}
		QState(QString _name)
		{
			QStateFun = nullptr;
			Name = _name;
		}

		QState(QStateBase _qb, QString _name)
		{
			QStateFun = _qb;
			Name = _name;
		}

		bool operator==(QState b)
		{
			return this->QStateFun == b.QStateFun;
		}
		bool operator==(std::nullptr_t)
		{
			return this == nullptr|| this->QStateFun == nullptr;
		}
		bool operator!=(std::nullptr_t)
		{
			return this != nullptr && this->QStateFun != nullptr;
		}
		void operator=(const QState& b)
		{
			this->QStateFun = b.QStateFun;
			this->Name = b.Name;
		}
		void operator=(std::nullptr_t)
		{
			this->QStateFun = nullptr;
			this->Name = nullptr;
		}
		bool operator!=(QState b)
		{
			return this->QStateFun != b.QStateFun;
		}

		//bool static operator==(QState a,QState b)
		//{
		//	return a.QStateFun == b.QStateFun;
		//}
		//bool static operator!=(QState a, QState b)
		//{
		//	return a.QStateFun != b.QStateFun;
		//}
	};


	typedef QState(*QStateCall)(void* const me, shared_ptr<IQEvent> qEvent);

#define Q_STATE_DECL(subclass_, state_) \
    static QState state_(void* const me, shared_ptr<IQEvent> qEvent)\
	{ \
        return static_cast<subclass_ *>(me)->state_ ## _handle(qEvent);\
	} \
    QState state_ ## _handle(shared_ptr<IQEvent> qEvent)

#define Q_STATE_DEF(subclass_, state_) \
    QState subclass_::state_ ## _handle(shared_ptr<IQEvent> qEvent)

#define Q_SET(pro,method)\
	pro=QState((QStateBase)method,#method);
}
