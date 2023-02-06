#include "QtStateActive.h"
QtStateActive::QtStateActive()
{
	testState->addState(A);
	testState->addState(B);
	testState->addState(C);
	testState->addState(D);
	testState->addState(E);
	testState->addState(F);

	testState->setInitialState(A); 
	connect(A, &QState::entered, this, &QtStateActive::onAEntry);
	connect(A, &QState::exited, this, &QtStateActive::onAExit);
	connect(B, &QState::entered, this, &QtStateActive::onBEntry);
	connect(C, &QState::entered, this, &QtStateActive::onCEntry);
	connect(D, &QState::entered, this, &QtStateActive::onDEntry);
	connect(E, &QState::entered, this, &QtStateActive::onEEntry);
	connect(F, &QState::entered, this, &QtStateActive::onFEntry);

	A->addTransition(this, &QtStateActive::startChangeSate, B);
	B->addTransition(C);
	C->addTransition(D);
	D->addTransition(E);
	E->addTransition(F);
	F->addTransition(A);
	finalTime = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
	testState->start();
	isWaitSignal = true;
}
void QtStateActive::onAExit()
{
	isWaitSignal = false;
	startTime = std::chrono::high_resolution_clock::now();
	
}
void QtStateActive::onAEntry()
{
	isWaitSignal = true;
	if (count != 0)
	{
		finalTime = finalTime + std::chrono::high_resolution_clock::now() - startTime;
	}
	count++;
}
void QtStateActive::onBEntry()
{
}
void QtStateActive::onCEntry()
{
}
void QtStateActive::onDEntry()
{
}
void QtStateActive::onEEntry()
{
}
void QtStateActive::onFEntry()
{
}

void QtStateActive::callSignal()
{
	emit startChangeSate();
}
void QtStateActive::stop()
{
	testState->stop();
}
void QtStateActive::start()
{
	testState->start();
}