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
	QHsmTest hsm;
	hsm.start(1);
	for (;;)
	{
		cout<<"currentThreadId:" << QThread::currentThreadId()<<endl << "Signal<-";
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
