#include <QCoreApplication>
#include "UserInterface/interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::API::Run();

    return a.exec();
}
