#pragma once
#include "../QF4CPlus/QHsm.h"
using namespace QtQf4CPlus;

class QHsmTest :
    public QHsm
{
public:
	QHsmTest()
	{
		m_s0 =(QState) s0;
	}
	~QHsmTest()
	{
	}
protected:
	void InitializeStateMachine() override
	{
		InitializeState(m_s0); // initial transition			
	}
    QState m_s0;

	static QState s0(void* const me, shared_ptr<IQEvent> qEvent)
	{
		return static_cast<QHsmTest*>(me)->s0_h(qEvent);
	}

	QState s0_h(shared_ptr<IQEvent> qEvent)
	{
		return TopState;
	}

};

