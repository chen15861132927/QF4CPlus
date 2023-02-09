#pragma once

#include "QHsm.h"
#include <QMetaMethod>
#include <qDebug>
using namespace QtQf4CPlus;
QString QHsm::_sTopState = "Top";

#pragma region  public method
QHsm::QHsm()
{
	m_myStateMethod = _sTopState;
	TopState = _sTopState;
	m_targetStateName = m_myStateMethod;

}
QHsm::~QHsm()
{
}

void QHsm::Init()
{
	const QMetaObject* metaobj = this->metaObject();
	//QString cname_1 = metaobj_1->className();
	for (int idx = metaobj->methodOffset(); idx < metaobj->methodCount(); ++idx)
	{
		QMetaMethod oneMethod = metaobj->method(idx);
		hash.insert(oneMethod.name(), oneMethod);
	}
	assert(m_myStateMethod == _sTopState);
	// save m_StateHandler in a temporary
	QString stateMethod = m_myStateMethod;

	InitializeStateMachine();
	// initial transition must go *one* level deep
	auto tempstate = GetSuperStateMethod(m_myStateMethod);
	m_targetStateName = m_myStateMethod;

	assert(tempstate == stateMethod);
	// Note: We only use the temporary
	stateMethod = m_myStateMethod;
	// variable stateMethod so that we can use Assert statements to ensure
	// that each transition is only one level deep.
	Trigger(stateMethod, QSignals::Entry);
	while (Trigger(stateMethod, QSignals::Init) == nullptr)
	{
		assert(GetSuperStateMethod(m_myStateMethod) == stateMethod);
		stateMethod = m_myStateMethod;

		Trigger(stateMethod, QSignals::Entry);
	}
}

void QHsm::Dispatch(shared_ptr<IQFEvent> qEvent)
{
	// We let the event bubble up the chain until it is handled by a state handler
	try
	{
		m_mySourceStateMethod = m_myStateMethod;
		while (m_mySourceStateMethod != nullptr)
		{
			StateTrace(m_mySourceStateMethod, qEvent->signal()); // ZTG-added
			QString state = TriggerByReflect(m_mySourceStateMethod, qEvent); //((QStateCall)m_mySourceStateMethod.QStateFun)(this, qEvent);

			if (state != nullptr)
			{
				m_mySourceStateMethod = state;
			}
			else
			{
				m_mySourceStateMethod = nullptr;
			}
		}
	}
	catch (const char* msg)
	{
		//TODO:: add log and stateMethod Name to track it.
	}
}

void QHsm::DispatchSynchronized(shared_ptr<IQFEvent> qEvent)
{
	Dispatch(qEvent);
}

QString QHsm::getCurrentStateName()
{
	return m_targetStateName;
}

#pragma endregion 
#pragma region protected method

void QHsm::InitializeState(QString state)
{
	m_myStateMethod = state;

	// try setting this in cases of transitionTo before any Dispatches
	m_mySourceStateMethod = m_myStateMethod;
	m_targetStateName = m_myStateMethod;

}

bool QHsm::IsInState(QString inquiredState)
{
	QString stateMethod = nullptr;
	for (stateMethod = m_myStateMethod;
		!stateMethod.isEmpty();
		stateMethod = GetSuperStateMethod(stateMethod))
	{
		if (stateMethod == inquiredState) // do the states match?
		{
			return true;
		}
	}

	return false; // no match found
}

void QHsm::TransitionTo(QString targetState)
{
	m_targetStateName = targetState;

	assert(targetState != TopState); // can't target 'top' state
	ExitUpToSourceState();
	// This is a dynamic transition. We pass in null instead of a recorder
	TransitionFromSourceToTarget(targetState, nullptr);
}

void QHsm::TransitionTo(QString targetState, shared_ptr<TransitionChain> transitionChain)
{
	assert(targetState != TopState); // can't target 'top' state			
	ExitUpToSourceState();

	if (transitionChain == nullptr) // for efficiency the first check is not thread-safe
	{
		// We implement the double-checked locking pattern
		TransitionToSynchronized(targetState, transitionChain);
	}
	else
	{
		// We just need to 'replay' the transition chain that is stored in the transitions chain.
		ExecuteTransitionChain(transitionChain);
	}
}
void QHsm::TransitionToSynchronized(QString targetState, shared_ptr<TransitionChain> transitionChain)
{
	if (transitionChain != nullptr)
	{
		// We encountered a race condition. The first (non-synchronized) check indicated that the transition chain
		// is null. However, a second threat beat us in getting into this synchronized method and populated
		// the transition chain in the meantime. We can execute the regular method again now.
		TransitionTo(targetState, transitionChain);
	}
	else
	{
		// The transition chain is not initialized yet, we need to dynamically retrieve
		// the required transition steps and record them so that we can subsequently simply
		// play them back.
		shared_ptr<TransitionChainRecorder>  recorder = make_shared<TransitionChainRecorder>();
		TransitionFromSourceToTarget(targetState, recorder);
		// We pass the recorded transition steps back to the caller:
		transitionChain = recorder->GetRecordedTransitionChain();
	}
}

void QHsm::ExecuteTransitionChain(shared_ptr<TransitionChain>  transitionChain)
{
	// There must always be at least one transition step in the provided transition chain
	assert(transitionChain->length() > 0);

	TransitionStep transitionStep = (*transitionChain)[0]; // to shut up the compiler; 
	// without it we would get the following error on the line 
	//       m_MyStateMethod = transitionStep.StateMethod;
	// at the end of this method: Use of possibly unassigned field 'State'
	for (int i = 0; i < transitionChain->length(); i++)
	{
		transitionStep = (*transitionChain)[i];
		Trigger(transitionStep.m_stateMethod, transitionStep.m_qSignal);
	}
	m_myStateMethod = transitionStep.m_stateMethod;
}

void QHsm::StateTrace(QString state, shared_ptr<QSignal> signal)
{
}
#pragma endregion 

#pragma region private method

QString QHsm::GetSuperStateMethod(QString stateMethod)
{
	QString superState = TriggerByReflect(stateMethod, make_shared<QFEvent>(QSignals::Empty)); //((QStateCall)stateMethod.QStateFun)(this, make_shared<QFEvent>(QSignals::Empty));

	if (superState != nullptr)
	{
		return superState;
	}
	else
	{
		return nullptr;
	}
}

QString QHsm::TriggerByReflect(QString stateMethod, shared_ptr<IQFEvent> qEvent)
{
	QMetaMethod triggerMethod=hash[stateMethod];
	QString state;
	if (triggerMethod.isValid())
	{
		triggerMethod.invoke(this, Qt::DirectConnection, Q_RETURN_ARG(QString, state), Q_ARG(shared_ptr<IQFEvent>, qEvent));
		return state;
	}
	else
	{
		return nullptr;
	}
}

QString QHsm::Trigger(QString stateMethod, shared_ptr<QSignal> qSignal)
{
	StateTrace(stateMethod, qSignal); // ZTG-added

	QString state = TriggerByReflect(stateMethod, make_shared<QFEvent>(qSignal));// = ((QStateCall)stateMethod.QStateFun)(this, make_shared<QFEvent>(qSignal));
	if (state == nullptr)
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
	for (auto stateMethod = m_myStateMethod; stateMethod != m_mySourceStateMethod;)
	{
		assert(stateMethod != nullptr);
		auto stateMethodToHandleExit = Trigger(stateMethod, QSignals::Exit);
		if (stateMethodToHandleExit != nullptr)
		{
			// state did not handle the Exit signal itself
			stateMethod = stateMethodToHandleExit;
		}
		else
		{
			// state handled the Exit signal. We need to elicit
			// the superstate explicitly.
			stateMethod = GetSuperStateMethod(stateMethod);
		}
	}
}

void QHsm::TransitionFromSourceToTarget(QString targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder)
{
	QList<QString> statesTargetToLca;
	int indexFirstStateToEnter = ExitUpToLca(targetStateMethod, statesTargetToLca, recorder);
	TransitionDownToTargetState(targetStateMethod, statesTargetToLca, indexFirstStateToEnter, recorder);
}


QString QHsm::Trigger(QString receiverStateMethod, shared_ptr<QSignal> qSignal, shared_ptr<TransitionChainRecorder>  recorder)
{
	QString stateMethod = Trigger(receiverStateMethod, qSignal);
	if (stateMethod == nullptr && recorder != nullptr)
	{
		// The receiverState handled the event
		recorder->Record(receiverStateMethod, qSignal);
	}
	return stateMethod;
}


int QHsm::ExitUpToLca(QString targetStateMethod, QList<QString>& statesTargetToLca, shared_ptr<TransitionChainRecorder>  recorder)
{
	statesTargetToLca.append(targetStateMethod);
	int indexFirstStateToEnter = 0;

	// (a) check my source state == target state (transition to self)
	if (m_mySourceStateMethod == targetStateMethod)
	{
		Trigger(m_mySourceStateMethod, QSignals::Exit, recorder);
		return indexFirstStateToEnter;
	}

	// (b) check my source state == super state of the target state
	QString targetSuperStateMethod = GetSuperStateMethod(targetStateMethod);
	//Debug.WriteLine(targetSuperStateMethod.Name);
	if (m_mySourceStateMethod == targetSuperStateMethod)
	{
		return indexFirstStateToEnter;
	}

	// (c) check super state of my source state == super state of target state
	// (most common)
	QString sourceSuperStateMethod = GetSuperStateMethod(m_mySourceStateMethod);
	if (sourceSuperStateMethod == targetSuperStateMethod)
	{
		Trigger(m_mySourceStateMethod, QSignals::Exit, recorder);
		return indexFirstStateToEnter;
	}

	// (d) check super state of my source state == target
	if (sourceSuperStateMethod == targetStateMethod)
	{
		Trigger(m_mySourceStateMethod, QSignals::Exit, recorder);
		indexFirstStateToEnter = -1; // we don't enter the LCA
		return indexFirstStateToEnter;
	}

	// (e) check rest of my source = super state of super state ... of target state hierarchy
	statesTargetToLca.append(targetSuperStateMethod);
	indexFirstStateToEnter++;
	for (QString stateMethod = GetSuperStateMethod(targetSuperStateMethod);
		stateMethod != nullptr; stateMethod = GetSuperStateMethod(stateMethod))
	{
		if (m_mySourceStateMethod == stateMethod)
		{
			return indexFirstStateToEnter;
		}

		statesTargetToLca.append(stateMethod);
		indexFirstStateToEnter++;
	}

	// For both remaining cases we need to exit the source state
	Trigger(m_mySourceStateMethod, QSignals::Exit, recorder);

	// (f) check rest of super state of my source state ==
	//     super state of super state of ... target state
	// The array list is currently filled with all the states
	// from the target state up to the top state
	for (int stateIndex = indexFirstStateToEnter; stateIndex >= 0; stateIndex--)
	{
		if (sourceSuperStateMethod == (QString)statesTargetToLca[stateIndex])
		{
			indexFirstStateToEnter = stateIndex - 1;
			// Note that we do not include the LCA state itself;
			// i.e., we do not enter the LCA
			return indexFirstStateToEnter;
		}
	}

	// (g) check each super state of super state ... of my source state ==
	//     super state of super state of ... target state
	for (QString stateMethod = sourceSuperStateMethod;
		stateMethod != nullptr; stateMethod = GetSuperStateMethod(stateMethod))
	{
		for (int stateIndex = indexFirstStateToEnter; stateIndex >= 0; stateIndex--)
		{
			if (stateMethod == (QString)statesTargetToLca[stateIndex])
			{
				indexFirstStateToEnter = stateIndex - 1;
				// Note that we do not include the LCA state itself;
				// i.e., we do not enter the LCA
				return indexFirstStateToEnter;
			}
		}
		Trigger(stateMethod, QSignals::Exit, recorder);
	}

	// We should never get here
	throw exception("Mal formed Hierarchical State Machine");
}


void QHsm::TransitionDownToTargetState(QString targetStateMethod, QList<QString>& statesTargetToLca,
	int indexFirstStateToEnter, shared_ptr<TransitionChainRecorder> recorder)
{
	// we enter the states in the passed in array in reverse order
	for (int stateIndex = indexFirstStateToEnter; stateIndex >= 0; stateIndex--)
	{
		Trigger((QString)statesTargetToLca[stateIndex], QSignals::Entry, recorder);
	}

	m_myStateMethod = targetStateMethod;

	// At last we are ready to initialize the target state.
	// If the specified target state handles init then the effective
	// target state is deeper than the target state specified in
	// the transition.
	while (Trigger(targetStateMethod, QSignals::Init, recorder) == nullptr)
	{
		// Initial transition must be one level deep
		assert(targetStateMethod == GetSuperStateMethod(m_myStateMethod));
		targetStateMethod = m_myStateMethod;
		Trigger(targetStateMethod, QSignals::Entry, recorder);
	}

	if (recorder != nullptr)
	{
		// We always make sure that the last entry in the recorder represents the entry to the target state.
		EnsureLastTransistionStepIsEntryIntoTargetState(targetStateMethod, recorder);
		assert(recorder->length() > 0);
	}
}

void QHsm::EnsureLastTransistionStepIsEntryIntoTargetState(QString targetStateMethod, shared_ptr<TransitionChainRecorder> recorder)
{
	if (recorder->length() == 0)
	{
		// Nothing recorded so far
		recorder->Record(targetStateMethod, QSignals::Entry);
		return;
	}
	else
	{
		// We need to test whether the last recorded transition step is the entry into the target state
		auto transitionChain = recorder->GetRecordedTransitionChain();
		TransitionStep lastTransitionStep = (*transitionChain)[transitionChain->length() - 1];
		if (lastTransitionStep.m_stateMethod != targetStateMethod ||
			lastTransitionStep.m_qSignal != QSignals::Entry)
		{
			recorder->Record(targetStateMethod, QSignals::Entry);
			return;
		}
	}
}
#pragma endregion
