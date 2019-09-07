#include <QCoreApplication>
#include "LocalInterface.h"
#include "slaves.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::LocalInterface interface(&a);

    Slaves my_slaves(&interface, "my_slaves");

    return a.exec();
}
