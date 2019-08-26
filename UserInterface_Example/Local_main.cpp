#include <QCoreApplication>
#include "LocalInterface.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::LocalInterface interface(&a);

    Worker worker(&interface, "Sam");

    return a.exec();
}
