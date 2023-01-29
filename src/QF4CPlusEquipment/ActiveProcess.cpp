#include "ActiveProcess.h"
 
shared_ptr<QSignal> ActiveProcess::SigInitialized = std::make_shared<QSignal>("Initialized");
shared_ptr<QSignal> ActiveProcess::SigStart = std::make_shared<QSignal>("Start");
shared_ptr<QSignal> ActiveProcess::SigStop = std::make_shared<QSignal>("Stop");
shared_ptr<QSignal> ActiveProcess::SigAbort = std::make_shared<QSignal>("Abort");
shared_ptr<QSignal> ActiveProcess::SigPause = std::make_shared<QSignal>("Pause");
shared_ptr<QSignal> ActiveProcess::SigResume = std::make_shared<QSignal>("Resume");
 