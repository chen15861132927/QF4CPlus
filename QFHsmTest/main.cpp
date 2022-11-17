#include <QtCore/QCoreApplication>
#include "QHsmTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QHsmTest hsm;

    hsm.Init();
    return a.exec();
}
