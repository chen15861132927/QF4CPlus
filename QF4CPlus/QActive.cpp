#include "QActive.h"
using namespace QtQf4CPlus;


QActive::QActive()
{
}
QActive::~QActive()
{
}
int QActive::GetPriority()
{
	return 0;
}

QString QActive::GetCurrentStateName()
{
	return "";
}

void QActive::Start(int priority)
{
}
void QActive::PostFIFO(shared_ptr<IQEvent> qEvent)
{

}
void QActive::PostLIFO(shared_ptr<IQEvent> qEvent)
{

}
bool QActive::IsInState(QState inquiredState)
{
	return true;
}