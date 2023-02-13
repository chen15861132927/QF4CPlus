#include "ActiveProcess.h"
QString ActiveProcess::stateInit(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Init", qEvent);

    if (qEvent->IsSignal(SigInitialized))
    {
        TransitionTo(m_stateIdle);
        return nullptr;
    }
    return TopState;
}

QString ActiveProcess::stateIdle(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Idle", qEvent);

    if (qEvent->IsSignal(SigStart))
    {
        TransitionTo(m_stateRunInit);
        return nullptr;
    }
    if (qEvent->IsSignal(SigError))
    {
        TransitionTo(m_stateIdleWithError);
        return nullptr;
    }
    return TopState;
}

QString ActiveProcess::stateIdleWithError(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("IdleWithError", qEvent);

    if (qEvent->IsSignal(SigResume))
    {
        TransitionTo(m_stateIdle);
        return nullptr;
    }
    return TopState;
}

QString ActiveProcess::stateActive(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Active", qEvent);

    if (qEvent->IsSignal(SigAbort))
    {
        LogMessage("Aborting from stateActive",qEvent);
        TransitionTo(m_stateAborting);
        return nullptr;
    }
    return TopState;
}

QString ActiveProcess::stateProcess(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Process", qEvent);

    if (qEvent->IsSignal(SigStop))
    {
        TransitionTo(m_stateStopping);
        return nullptr;
    }
    if (qEvent->IsSignal(SigPause))
    {
        stateHistory = targetState;
        TransitionTo(m_statePause);
        return nullptr;
    }
    if (qEvent->IsSignal(SigError))
    {
        TransitionTo(m_stateError);
        return nullptr;
    }
    if (qEvent->IsSignal(SigRecover))
    {
        /*string str = string.Format("Unhandled SigRecover signal! ErrorButton: {0}", errorMessage.UserSelected.Name);
        MessageBox.Show(str);*/
        return nullptr;
    }
    return m_stateActive;
}

QString ActiveProcess::stateRunInit(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("RunInit", qEvent);

    if (qEvent->IsSignal(SigStateJob))
    {
        ClearDeferredSignals();
        TransitionTo(m_stateRun);
        return nullptr;
    }

    return m_stateProcess;
}

QString ActiveProcess::stateRun(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Run", qEvent);

    if (qEvent->IsSignal(SigStop))
    {
        TransitionTo(m_stateStopping);
        return nullptr;
    }
    return m_stateProcess;
}

QString ActiveProcess::statePaused(shared_ptr<IQFEvent> qEvent)         // parent state of Pausing, Error, WaitToResume
{
    LogMessage("Paused", qEvent);

    if (qEvent->IsSignal(SigStop))
    {
        TransitionTo(m_stateStopping);
        return nullptr;
    }
    if (qEvent->IsSignal(SigAbort))
    {
        TransitionTo(m_stateAborting);
        return nullptr;
    }
    return m_stateActive;
}

QString ActiveProcess::stateError(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Error", qEvent);

    if (qEvent->IsSignal(SigStateJob))
    {
        // figure out if a custom error message has been created

        // pass error to Error Handler Service
        DefaultErrorHandler();
        return nullptr;
    }
    if (qEvent->IsSignal(SigResume))
    {
        //TODO::
        //if (errorMessage.UserSelected == ParselErrorButtonList.Abort)
        //{
        //    parentWorkcell.MainProcess.Abort();
        //}
        //else if (errorMessage.UserSelected == ParselErrorButtonList.Retry)
        //{
        //    // transition to the run sub-state, but DON'T post the statejob signal yet...
        //    targetState = stateHistory;
        //    base.TransitionToWithoutJob(targetState);
        //    // The target state can retrieve the retry button hit, if desired
        //    // create the stateJob signal and embed the retry option from the operator
        //    QEvent retryEvent = new QEvent(SigStateJob)
        //    {
        //        EventObject = errorMessage.UserSelected
        //    };
        //    PostFIFO(retryEvent);
        //}
        //else if (errorMessage.UserSelected == ParselErrorButtonList.Stop)
        //{
        //    parentWorkcell.MainProcess.Stop();
        //}
        //else
        //{
        //    // transition to the run sub-state, but DON'T post the statejob signal
        //    targetState = stateHistory;
        //    base.TransitionToWithoutJob(targetState);
        //    // The target state will retrieve the button hit 
        //    // create the recovery signal and embed the recovery option from the operator
        //    QEvent recoverEvent = new QEvent(SigRecover)
        //    {
        //        EventObject = errorMessage.UserSelected
        //    };
        //    PostFIFO(recoverEvent);
        //}
        return nullptr;
    }
    return m_statePaused;
}

QString ActiveProcess::statePause(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Pause", qEvent);

    if (qEvent->IsSignal(SigStateJob))
    {
        // perform action required to pause, i.e. park servos
        return nullptr;
    }
    if (qEvent->IsSignal(SigResume))
    {
        TransitionTo(stateHistory);
        return nullptr;
    }
    return m_statePaused;
}

QString ActiveProcess::stateAborting(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Aborting", qEvent);

    if (qEvent->IsSignal(SigStateJob))
    {
        TransitionTo(m_stateIdle);
        return nullptr;
    }
    return m_stateActive;
}

QString ActiveProcess::stateStopping(shared_ptr<IQFEvent> qEvent)
{
    LogMessage("Stopping", qEvent);

    if (qEvent->IsSignal(SigStateJob))
    {
        TransitionTo(m_stateIdle);
        return nullptr;
    }
    return m_stateActive;
}
