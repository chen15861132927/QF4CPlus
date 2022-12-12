#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QF4CPlus_VS_QtStateMachine.h"
#include "QFActive.h"
#include "QtStateActive.h"

class QF4CPlus_VS_QtStateMachine : public QMainWindow
{
    Q_OBJECT

       
public:
    QF4CPlus_VS_QtStateMachine(QWidget *parent = Q_NULLPTR);
    QFActive qFActive;
    QtStateActive qtStateActive;

    static int TestCount;
    QTimer * QFStateTimerReader;
    QTimer* QTStateTimerReader;

private:
    void onQF4Clicked();
    void onQT4Clicked();
    void onQFTimeoutShow();
    void onQTTimeoutShow();

    Ui::QF4CPlus_VS_QtStateMachineClass ui;
};
