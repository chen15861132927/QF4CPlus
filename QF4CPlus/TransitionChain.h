#pragma once
#include <QList>
#include "QState.h"
#include "QSignal.h"

using namespace std;

namespace QtQf4CPlus
{
    struct TransitionStep
    {
        QState m_stateMethod;
        shared_ptr<QSignal> m_qSignal;

        TransitionStep(QState _stateMethod, shared_ptr<QSignal>  _qSignal)
        {
            m_stateMethod = _stateMethod;
            m_qSignal = _qSignal;
        }
    };
    class TransitionChain
    {
    public:
        TransitionChain()
        {
        }
        TransitionChain(QList<TransitionStep> &_transitionSteps)
        {
            for (int i = 0; i < _transitionSteps.length(); i++)
            {
                m_stateMethodChain.append(_transitionSteps[i]);
            }
        }

        int length()
        {
            return m_stateMethodChain.length();
        }

        TransitionStep& operator[](int i)
        {
            return m_stateMethodChain[i];
        }
        const TransitionStep& operator[](int i) const
        {
            return m_stateMethodChain[i];
        }
        void append(TransitionStep _transitionStep)
        {
            m_stateMethodChain.append(_transitionStep);
        }
    private:
        QList<TransitionStep> m_stateMethodChain;
        //  holds the transitions that need to be performed from the LCA down to the target state
    };
}