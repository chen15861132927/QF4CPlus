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
		m_s1= (QState) s1;
	}
	~QHsmTest()
	{
	}

private:
	QState m_s0;
	QState m_s1;
protected:

	void InitializeStateMachine() override
	{
		InitializeState(m_s0); // initial transition			
	}

	Q_STATE(QHsmTest, s0);

	Q_STATE(QHsmTest, s1);
};

