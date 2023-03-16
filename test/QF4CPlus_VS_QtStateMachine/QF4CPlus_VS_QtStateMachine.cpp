#include "QF4CPlus_VS_QtStateMachine.h"
#include <QTimer>
#include "../../src/QF4CPlus/QF.h"
#include <QThread>
int QF4CPlus_VS_QtStateMachine::TestCount = 10000;
QF4CPlus_VS_QtStateMachine::QF4CPlus_VS_QtStateMachine(QWidget* parent)
	: QMainWindow(parent)
{
	QFStateTimerReader = new QTimer;
	ui.setupUi(this);
	connect(ui.push_QF4Start, &QPushButton::clicked, this, &QF4CPlus_VS_QtStateMachine::onQF4Clicked);
	connect(QFStateTimerReader, &QTimer::timeout, this, &QF4CPlus_VS_QtStateMachine::onQFTimeoutShow); //定义计时器，并连接槽函数
	qFActive = std::make_shared<QFActive>();
	QF::getInstance()->Subscribe(qFActive, qFActive->Start_Sig);


	QTStateTimerReader = new QTimer;

	connect(QTStateTimerReader, &QTimer::timeout, this, &QF4CPlus_VS_QtStateMachine::onQTTimeoutShow); //定义计时器，并连接槽函数
	connect(ui.push_QTStart, &QPushButton::clicked, this, &QF4CPlus_VS_QtStateMachine::onQT4Clicked);
	connect(ui.oneclickbtn, &QPushButton::clicked, this, [=]() {
		QTimer::singleShot(0, this, [=]()
			{
				QF::getInstance()->Publish(make_shared<QFEvent>(qFActive->Start_Sig));
			});
		});
}
void QF4CPlus_VS_QtStateMachine::onQF4Clicked()
{
	QFStateTimerReader->start(1);
	qFActive->start(1);
}
void QF4CPlus_VS_QtStateMachine::onQFTimeoutShow()
{
	long current = qFActive->getCurrentCount();
	ui.qFCount->setText(QString::number(current));
	if (current >= QF4CPlus_VS_QtStateMachine::TestCount)
	{
		QFStateTimerReader->stop();
		long mestime = std::chrono::duration_cast<std::chrono::milliseconds>(qFActive->finalTime).count();
		ui.QFAllTime->setText(QString::number(mestime) + "milliseconds");
	}
	if (qFActive->getCurrentStateName() == "sA")
	{
		//qDebug() << "call qFActive onQFTimeoutShow" << endl;

		QTimer::singleShot(0, this, [=]()
			{
				QF::getInstance()->Publish(make_shared<QFEvent>(qFActive->Start_Sig));
			});
		//QThread::sleep(1);
	}
}

void QF4CPlus_VS_QtStateMachine::onQT4Clicked()
{
	QTStateTimerReader->start(1);
	qtStateActive.start();
	qtStateActive.callSignal();

}
void QF4CPlus_VS_QtStateMachine::onQTTimeoutShow()
{
	long current = qtStateActive.getCurrentCount();
	ui.QTCount->setText(QString::number(current));
	if (current >= QF4CPlus_VS_QtStateMachine::TestCount)
	{
		qtStateActive.stop();
		long mestime = std::chrono::duration_cast<std::chrono::milliseconds>(qtStateActive.finalTime).count();
		ui.QTAlltime->setText(QString::number(mestime) + "milliseconds");
	}
	if (qtStateActive.isWaitSignal)
	{
		QTimer::singleShot(0, this, [=]()
			{
				qtStateActive.callSignal();
			});
	}
}
