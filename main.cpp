#include <QCoreApplication>
#include "UserInterface/interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UserInterface::Interface::getInstance()->run();

//    auto i = UserInterface::Interface();
//    i.run();

    return a.exec();
}
