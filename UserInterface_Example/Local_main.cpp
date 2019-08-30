#include <QCoreApplication>
#include "LocalInterface.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::LocalInterface interface(&a);

    Worker worker1(&interface, "Sam");

    Worker worker2(&interface, "Bob");

    return a.exec();
}
