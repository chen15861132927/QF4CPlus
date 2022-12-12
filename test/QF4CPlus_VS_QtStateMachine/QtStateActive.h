#pragma once
#include <QStateMachine>
class QtStateActive:public QObject
{
    Q_OBJECT
public:
    QtStateActive();
    void onAExit();
    void onAEntry();
    void onBEntry();
    void onCEntry();
    void onDEntry();
    void onEEntry();
    void onFEntry();
    void callSignal();
    int getCurrentCount()
    {
        return count;
    }
    void stop();
    void start();
    std::chrono::nanoseconds finalTime;

    bool isWaitSignal = false;
signals:
    void startChangeSate();
private:
	QStateMachine* testState=new QStateMachine;
    // 创建状态对象
    QState* A = new QState(testState);
    QState* B = new QState(testState);
    QState* C = new QState(testState);
    QState* D = new QState(testState);
    QState* E = new QState(testState);
    QState* F = new QState(testState);


    std::chrono::steady_clock::time_point startTime;

    int count = 0;

};

