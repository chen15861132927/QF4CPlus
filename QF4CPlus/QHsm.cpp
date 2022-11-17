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
		assert(_mMyStateMethod == _sTopState); 
		// save m_StateHandler in a temporary
		QState stateMethod = _mMyStateMethod; 

		InitializeStateMachine();  
		// initial transition must go *one* level deep
		auto tempstate = GetSuperStateMethod(_mMyStateMethod);
		assert(tempstate == stateMethod);
		// Note: We only use the temporary
		stateMethod = _mMyStateMethod; 
		// variable stateMethod so that we can use Assert statements to ensure
		// that each transition is only one level deep.
		Trigger(stateMethod, QSignals::Entry);
		while (Trigger(stateMethod, QSignals::Init) == nullptr)  
		{
			assert(GetSuperStateMethod(_mMyStateMethod) == stateMethod);
			stateMethod = _mMyStateMethod;

			Trigger(stateMethod, QSignals::Entry);
		}
	}

	void QHsm::Dispatch(shared_ptr<IQEvent> qEvent)
	{
		// We let the event bubble up the chain until it is handled by a state handler
		try
		{
			_mMySourceStateMethod = _mMyStateMethod;
			while (_mMySourceStateMethod != nullptr)
			{
				StateTrace(_mMySourceStateMethod, qEvent->GetQSignal()); // ZTG-added
				QState state = (QState)_mMySourceStateMethod(this, qEvent);
				if (state != nullptr)
				{
					_mMySourceStateMethod = state;
				}
				else
				{
					_mMySourceStateMethod = nullptr;
				}
			}
		}
		catch (const char* msg)
		{
			//TODO:: add log and stateMethod Name to track it.
		}
	}

	void QHsm::DispatchSynchronized(shared_ptr<IQEvent> qEvent)
	{
		Dispatch(qEvent);
	}

#pragma endregion 
#pragma region protected method

	void QHsm::InitializeState(QState state)
	{
		_mMyStateMethod = state;

		// try setting this in cases of transitionTo before any Dispatches
		_mMySourceStateMethod = _mMyStateMethod;
	}

	bool QHsm::IsInState(QState inquiredState)
	{
		QState stateMethod;
		for (stateMethod = _mMyStateMethod;
			stateMethod != nullptr;
			stateMethod = GetSuperStateMethod(stateMethod))
		{
			if (stateMethod == inquiredState) // do the states match?
			{
				return true;
			}
		}

		return false; // no match found
	}
	void QHsm::StateTrace(QState state, shared_ptr<QSignal> signal)
	{
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