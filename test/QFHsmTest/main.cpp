#include <QtCore/QCoreApplication>
#include "QHsmTest.h"
#include <iostream>
#include "QEvent.h"
#include "../../src/QF4CPlus/QActive.h"
#include "../../src/QF4CPlus/QF.h"

using namespace QtQf4CPlus;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	QList<std::shared_ptr<QHsmTest>> actives;
	for (int i = 0; i < 1000; i++)
	{
		auto act = std::make_shared<QHsmTest>();
		act->setObjectName(QString("QHsmTest%1").arg(i));
		actives.append(act);
	}
	for (int i = 0; i < actives.length(); i++)
	{
		actives[i]->start(i);
	}

	for (;;)
	{
		qDebug() << "ThreadObjectName:" << QThread::currentThread()->objectName()  << endl << "input Signal(1-5):";

		char inputchar;
		cin >> inputchar;
		if (inputchar == -1)
		{
			break;
		}
		else
		{
			if (inputchar < (int)'1' || inputchar >(int)'5')
			{
				break;
			}
			else
			{
				auto input = QSignals::Empty;
				if (inputchar - '1' + (int)(*MyQSignals::E1_Sig) == (int)(*MyQSignals::E1_Sig))
				{
					input = MyQSignals::E1_Sig;
				}
				else if (inputchar - '1' + (int)(*MyQSignals::E1_Sig) == (int)(*MyQSignals::E2_Sig))
				{
					input = MyQSignals::E2_Sig;
				}
				else if (inputchar - '1' + (int)(*MyQSignals::E1_Sig) == (int)(*MyQSignals::E3_Sig))
				{
					input = MyQSignals::E3_Sig;
				}
				else if (inputchar - '1' + (int)(*MyQSignals::E1_Sig) == (int)(*MyQSignals::E4_Sig))
				{
					input = MyQSignals::E4_Sig;
				}
				else if (inputchar - '1' + (int)(*MyQSignals::E1_Sig) == (int)(*MyQSignals::E5_Sig))
				{
					input = MyQSignals::E5_Sig;
				}
				QF::getInstance()->Publish(make_shared<QtQf4CPlus::QFEvent>(input));
				//hsm.Dispatch(make_shared<QtQf4CPlus::QFEvent>(input));
			}
		}
	}
    return a.exec();
}
