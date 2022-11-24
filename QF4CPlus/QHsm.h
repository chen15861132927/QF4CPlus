#pragma once
#include <QString>
#include "qf4cplus_global.h"
#include <QObject>
#include "QState.h"
#include "IQHsm.h"
#include "QEvent.h"
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
			void Record(QState stateMethod, shared_ptr<QSignal> signal)
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
		void Dispatch(shared_ptr<IQEvent> qEvent);

	private:
		QState m_myStateMethod;
		QState m_mySourceStateMethod;
		QString m_targetStateName;

		static shared_ptr<QState> _sTopState;

		static QState Top(shared_ptr<IQEvent> qEvent)
		{
			QState empty("Top");
			return empty;
		}

		QState GetSuperStateMethod(QState stateMethod);

		QState Trigger(QState stateMethod, shared_ptr<QSignal> qSignal);
		QState Trigger(QState receiverStateMethod, shared_ptr<QSignal> qSignal, shared_ptr<TransitionChainRecorder>  recorder);

		void ExitUpToSourceState();
		void TransitionFromSourceToTarget(QState targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder);

		int ExitUpToLca(QState targetStateMethod, QList<QState>& statesTargetToLca, shared_ptr<TransitionChainRecorder>  recorder);
		void TransitionDownToTargetState(QState targetStateMethod, QList<QState>& statesTargetToLca, int indexFirstStateToEnter, shared_ptr<TransitionChainRecorder>  recorder);
		void EnsureLastTransistionStepIsEntryIntoTargetState(QState targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder);
		void TransitionToSynchronized(QState targetState, shared_ptr<TransitionChain> transitionChain);
		void ExecuteTransitionChain(shared_ptr<TransitionChain>  transitionChain);

	protected:

		void InitializeState(QState state);

		bool IsInState(QState inquiredState);


		void DispatchSynchronized(shared_ptr<IQEvent> qEvent);

		QState TopState;
		void TransitionTo(QState targetState);

		void StateTrace(QState state, shared_ptr<QSignal> signal);
		void TransitionTo(QState targetState, shared_ptr<TransitionChain> transitionChain);


	};
};