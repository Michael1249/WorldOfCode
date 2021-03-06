#include <QCoreApplication>
#include "UserInterface/LocalInterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::LocalInterface interface(&a);

    return a.exec();
}
