#include "QF4CPlus_VS_QtStateMachine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QF4CPlus_VS_QtStateMachine w;
    w.show();
    return a.exec();
}
