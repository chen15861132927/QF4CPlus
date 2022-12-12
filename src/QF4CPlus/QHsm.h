#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QState.h"
#include "Interfaces/IQHsm.h"
#include "QFEvent.h"
#include "QSignal.h"
#include "QSignals.h"
#include "TransitionChain.h"
#include "TransitionChain.h"
namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QHsm :public IQHsm
	{
#pragma region private class
	private:
		class TransitionChainRecorder
		{
		public:
			TransitionChainRecorder()
			{
			}
		private:
			TransitionChain m_transitionSteps;
		public:
			void Record(QFState stateMethod, shared_ptr<QSignal> signal)
			{
				m_transitionSteps.append(TransitionStep(stateMethod, signal));
			}

			/// <summary>
			/// Returns the recorded transition steps in form of a <see cref="TransitionChain"/> instance.
			/// </summary>
			/// <returns></returns>
			shared_ptr<TransitionChain> GetRecordedTransitionChain()
			{
				// We turn the ArrayList into a strongly typed array
				return make_shared<TransitionChain>(m_transitionSteps);
			}

			bool operator==(std::nullptr_t)
			{
				return this == nullptr;
			}
			bool operator!=(std::nullptr_t)
			{
				return this != nullptr;
			}

			int length()
			{
				return m_transitionSteps.length();
			}
		};

#pragma endregion


	public:
		QHsm();
		~QHsm();
		void Init();
		QString getCurrentStateName();
		void Dispatch(shared_ptr<IQFEvent> qEvent);

	private:
		QFState m_myStateMethod;
		QFState m_mySourceStateMethod;
		QString m_targetStateName;

		static shared_ptr<QFState> _sTopState;

		static QFState Top(shared_ptr<IQFEvent> qEvent)
		{
			QFState empty("Top");
			return empty;
		}

		QFState GetSuperStateMethod(QFState stateMethod);

		QFState Trigger(QFState stateMethod, shared_ptr<QSignal> qSignal);
		QFState Trigger(QFState receiverStateMethod, shared_ptr<QSignal> qSignal, shared_ptr<TransitionChainRecorder>  recorder);

		void ExitUpToSourceState();
		void TransitionFromSourceToTarget(QFState targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder);

		int ExitUpToLca(QFState targetStateMethod, QList<QFState>& statesTargetToLca, shared_ptr<TransitionChainRecorder>  recorder);
		void TransitionDownToTargetState(QFState targetStateMethod, QList<QFState>& statesTargetToLca, int indexFirstStateToEnter, shared_ptr<TransitionChainRecorder>  recorder);
		void EnsureLastTransistionStepIsEntryIntoTargetState(QFState targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder);
		void TransitionToSynchronized(QFState targetState, shared_ptr<TransitionChain> transitionChain);
		void ExecuteTransitionChain(shared_ptr<TransitionChain>  transitionChain);

	protected:

		void InitializeState(QFState state);

		bool IsInState(QFState inquiredState);


		void DispatchSynchronized(shared_ptr<IQFEvent> qEvent);

		QFState TopState;
		void TransitionTo(QFState targetState);

		void StateTrace(QFState state, shared_ptr<QSignal> signal);
		void TransitionTo(QFState targetState, shared_ptr<TransitionChain> transitionChain);


	};
};