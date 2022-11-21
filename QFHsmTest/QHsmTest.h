#pragma once
#include "../QF4CPlus/QHsm.h"
using namespace QtQf4CPlus;

class QHsmTest :
    public QHsm
{
public:
	QHsmTest();
	~QHsmTest();

private:
	QState m_s0;
	QState m_s1;

protected:
	void InitializeStateMachine() override;

	Q_STATE(QHsmTest, s0);
	/*static QState s0(void* const me, shared_ptr<IQEvent> qEvent)
	{
		auto temp = static_cast<QHsmTest*>(me);
		return temp->s0_call(qEvent);
	}

	QState s0_call(shared_ptr<IQEvent> qEvent)
	{
		return TopState;
	}*/
	Q_STATE(QHsmTest, s1);

	/*static QState s1(void* const me, shared_ptr<IQEvent> qEvent)
	{ 
		auto temp = static_cast<QHsmTest*>(me);
		return temp->s1_call(qEvent);
	} 

	QState s1_call(shared_ptr<IQEvent> qEvent)
	{
		return nullptr;
	}*/
};

