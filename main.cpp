#include <QCoreApplication>
#include "UserInterface/Interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::Interface interface(&a);

    return a.exec();
}
