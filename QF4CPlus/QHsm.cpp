#pragma once

#include "QHsm.h"
#include "QEvent.h"
#include "QSignal.h"
#include "QSignals.h"
namespace QtQf4CPlus
{
	shared_ptr<QState> QHsm::_sTopState =make_shared<QState>((QStateBase)QHsm::Top,("Top"));

#pragma region  public method
	QHsm::QHsm()
	{
		m_MyStateMethod = *_sTopState;
		TopState = *_sTopState;
	}
	QHsm::~QHsm()
	{
	}

	void QHsm::Init()
	{
		assert(m_MyStateMethod.QStateFun == _sTopState->QStateFun);
		// save m_StateHandler in a temporary
		QState stateMethod = m_MyStateMethod; 

		InitializeStateMachine();  
		// initial transition must go *one* level deep
		auto tempstate = GetSuperStateMethod(m_MyStateMethod);
		assert(tempstate == stateMethod);
		// Note: We only use the temporary
		stateMethod = m_MyStateMethod; 
		// variable stateMethod so that we can use Assert statements to ensure
		// that each transition is only one level deep.
		Trigger(stateMethod, QSignals::Entry);
		while (Trigger(stateMethod, QSignals::Init) == nullptr)  
		{
			assert(GetSuperStateMethod(m_MyStateMethod) == stateMethod);
			stateMethod = m_MyStateMethod;

			Trigger(stateMethod, QSignals::Entry);
		}
	}

	void QHsm::Dispatch(shared_ptr<IQEvent> qEvent)
	{
		// We let the event bubble up the chain until it is handled by a state handler
		try
		{
			m_MySourceStateMethod = m_MyStateMethod;
			while (m_MySourceStateMethod != nullptr)
			{
				StateTrace(m_MySourceStateMethod, qEvent->GetQSignal()); // ZTG-added
				QState state = ((QStateCall)m_MySourceStateMethod.QStateFun)(this, qEvent);

				if (state != nullptr)
				{
					m_MySourceStateMethod = state;
				}
				else
				{
					m_MySourceStateMethod.QStateFun = nullptr;
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
		m_MyStateMethod = state;

		// try setting this in cases of transitionTo before any Dispatches
		m_MySourceStateMethod = m_MyStateMethod;
	}

	bool QHsm::IsInState(QState inquiredState)
	{
		QState stateMethod=nullptr;
		for (stateMethod = m_MyStateMethod;
			stateMethod.QStateFun != nullptr;
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
		QState superState = ((QStateCall)stateMethod.QStateFun)(this, make_shared<QEvent>(QSignals::Empty));

		if (superState.QStateFun != nullptr)
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
		QState state = ((QStateCall)stateMethod.QStateFun)(this, make_shared<QEvent>(qSignal));
		if (state.QStateFun == nullptr)
		{
			return nullptr;
		}
		else
		{
			return state;
		}
	}

	void QHsm::ExitUpToSourceState()
	{
		QState methodInfo = m_MyStateMethod;
		while (methodInfo != m_MySourceStateMethod)
		{
			QState methodInfo2 = Trigger(methodInfo, QSignals::Exit);
			methodInfo = ((!(methodInfo2.QStateFun != nullptr)) ? GetSuperStateMethod(methodInfo) : methodInfo2);
		}
	}
#pragma endregion

};