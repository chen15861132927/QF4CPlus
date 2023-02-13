#include "EquipmentActiveBase.h"

shared_ptr<QSignal> EquipmentActiveBase::SigInitialized = std::make_shared<QSignal>("Initialized");
shared_ptr<QSignal> EquipmentActiveBase::SigStart = std::make_shared<QSignal>("Start");
shared_ptr<QSignal> EquipmentActiveBase::SigStop = std::make_shared<QSignal>("Stop");
shared_ptr<QSignal> EquipmentActiveBase::SigAbort = std::make_shared<QSignal>("Abort");
shared_ptr<QSignal> EquipmentActiveBase::SigPause = std::make_shared<QSignal>("Pause");
shared_ptr<QSignal> EquipmentActiveBase::SigResume = std::make_shared<QSignal>("Resume");
