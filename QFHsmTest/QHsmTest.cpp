#include "QHsmTest.h"

QHsmTest::QHsmTest()
{
	Q_SET(m_s0, s0);
	Q_SET(m_s1, s1);
}

QHsmTest::~QHsmTest()
{
}

void QHsmTest::InitializeStateMachine()
{
	InitializeState(m_s0); // initial transition			
}

Q_STATEFUN(QHsmTest, s0)
{
	return TopState;
}
Q_STATEFUN(QHsmTest, s1)
{
	return nullptr;
}
