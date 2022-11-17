#pragma once

#include "QHsm.h"
#include "QEvent.h"
#include "QSignal.h"
#include "QSignals.h"
namespace QtQf4CPlus
{
	QState QHsm::_sTopState =(QState)QHsm::Top;
#pragma region  public method
	QHsm::QHsm()
	{
		_mMyStateMethod = _sTopState;
		TopState = _sTopState;
	}
	QHsm::~QHsm()
	{
	}

	void QHsm::Init()
	{
		assert(_mMyStateMethod == _sTopState); // HSM not executed yet
		QState stateMethod = _mMyStateMethod; // save m_StateHandler in a temporary

		InitializeStateMachine(); // We call into the deriving class
		// initial transition must go *one* level deep
		auto tempstate = GetSuperStateMethod(_mMyStateMethod);
		assert(tempstate == stateMethod);
		stateMethod = _mMyStateMethod; // Note: We only use the temporary
		//// variable stateMethod so that we can use Assert statements to ensure
		//// that each transition is only one level deep.
		Trigger(stateMethod, QSignals::Entry);
		while (Trigger(stateMethod, QSignals::Init) == nullptr) // init handled?
		{
			assert(GetSuperStateMethod(_mMyStateMethod) == stateMethod);
			stateMethod = _mMyStateMethod;

			Trigger(stateMethod, QSignals::Entry);
		}
	}
#pragma endregion 
#pragma region protected method

	void QHsm::InitializeState(QState state)
	{
		_mMyStateMethod = state;

		// try setting this in cases of transitionTo before any Dispatches
		_mMySourceStateMethod = _mMyStateMethod;
	}

#pragma endregion 
#pragma region private method

	QState QHsm::GetSuperStateMethod(QState stateMethod)
	{
		QState superState = (QState)stateMethod(this, make_shared<QEvent>(QSignals::Empty));
		if (superState != nullptr)
		{
			return superState;
		}
		else
		{
			return nullptr;
		}
	}

	QState QHsm::Trigger(QState stateMethod, shared_ptr<QSignal> qSignal)
	{
		StateTrace(stateMethod, qSignal); // ZTG-added
		QState state = (QState)stateMethod(this, make_shared<QEvent>(qSignal));
		if (state == nullptr)
		{
			return nullptr;
		}
		else
		{
			return state;
		}
	}
#pragma endregion

};