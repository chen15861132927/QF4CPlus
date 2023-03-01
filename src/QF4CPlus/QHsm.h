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

#define Q_STATE_DECL(state_) \
	Q_INVOKABLE QString state_(shared_ptr<IQFEvent> qEvent);\
	const QString m_##state_ = #state_;\


namespace QtQf4CPlus
{
	class QF4CPLUS_EXPORT QHsm :public QObject,public IQHsm
	{
		Q_OBJECT
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
			void Record(QString stateMethod, shared_ptr<QSignal> signal)
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
		QString m_myStateMethod;
		QString m_mySourceStateMethod;
		QString m_targetStateName;

		static QString _sTopState;

		QHash<QString, QMetaMethod> hash;

		//static QString Top(shared_ptr<IQFEvent> qEvent)
		//{
		//	QString empty("Top");
		//	return empty;
		//}

		QString GetSuperStateMethod(QString stateMethod);
		QString TriggerByReflect(QString stateMethod, shared_ptr<IQFEvent> qEvent);
		QString Trigger(QString stateMethod, shared_ptr<QSignal> qSignal);
		QString Trigger(QString receiverStateMethod, shared_ptr<QSignal> qSignal, shared_ptr<TransitionChainRecorder>  recorder);

		void ExitUpToSourceState();
		void TransitionFromSourceToTarget(QString targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder);

		int ExitUpToLca(QString targetStateMethod, QList<QString>& statesTargetToLca, shared_ptr<TransitionChainRecorder>  recorder);
		void TransitionDownToTargetState(QString targetStateMethod, QList<QString>& statesTargetToLca, int indexFirstStateToEnter, shared_ptr<TransitionChainRecorder>  recorder);
		void EnsureLastTransistionStepIsEntryIntoTargetState(QString targetStateMethod, shared_ptr<TransitionChainRecorder>  recorder);
		void TransitionToSynchronized(QString targetState, shared_ptr<TransitionChain> transitionChain);
		void ExecuteTransitionChain(shared_ptr<TransitionChain>  transitionChain);

	protected:

		void InitializeState(QString state);

		bool IsInState(QString inquiredState);

		void DispatchSynchronized(shared_ptr<IQFEvent> qEvent);

		QString TopState;
		void TransitionTo(QString targetState);

		void StateTrace(QString state, shared_ptr<QSignal> signal);
		void TransitionTo(QString targetState, shared_ptr<TransitionChain> transitionChain);


	};
};