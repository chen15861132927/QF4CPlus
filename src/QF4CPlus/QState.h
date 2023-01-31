#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "Signal.h"
#include "Interfaces/IQFEvent.h"
#include <functional>
#include <memory>

using namespace std;

namespace QtQf4CPlus
{
	typedef void* (*QStateBase)(void* const me, shared_ptr<IQFEvent> qEvent);

	struct QFState :QObject
	{
		QStateBase QStateFun;
		QString Name;
		QFState(const QFState& b)
		{
			QStateFun = b.QStateFun;
			Name = b.Name;
		}
		QFState()
		{
			QStateFun = nullptr;
			Name = nullptr;
		}
		QFState(QString _name)
		{
			QStateFun = nullptr;
			Name = _name;
		}

		QFState(QStateBase _qb, QString _name)
		{
			QStateFun = _qb;
			Name = _name;
		}

		bool operator==(QFState b)
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
		void operator=(const QFState& b)
		{
			this->QStateFun = b.QStateFun;
			this->Name = b.Name;
		}
		void operator=(std::nullptr_t)
		{
			this->QStateFun = nullptr;
			this->Name = nullptr;
		}
		bool operator!=(QFState b)
		{
			return this->QStateFun != b.QStateFun;
		}

		//bool static operator==(QFState a,QFState b)
		//{
		//	return a.QStateFun == b.QStateFun;
		//}
		//bool static operator!=(QFState a, QFState b)
		//{
		//	return a.QStateFun != b.QStateFun;
		//}
	};


	typedef QFState(*QStateCall)(void* const me, shared_ptr<IQFEvent> qEvent);

#define Q_STATE_DECL(subclass_, state_) \
    static QFState state_(void* const me, shared_ptr<IQFEvent> qEvent)\
	{ \
        return static_cast<subclass_ *>(me)->state_ ## _handle(qEvent);\
	} \
    QFState state_ ## _handle(shared_ptr<IQFEvent> qEvent)

#define Q_STATE_DEF(subclass_, state_) \
    QFState subclass_::state_ ## _handle(shared_ptr<IQFEvent> qEvent)

#define Q_SET(pro,method)\
	pro=QFState((QStateBase)method,#method);


#define Q_Static_DECL(subclass_, state_,handle_) \
    static QFState state_(void* const me, shared_ptr<IQFEvent> qEvent)\
	{ \
        return static_cast<subclass_ *>(me)->handle_(qEvent);\
	} 
}
