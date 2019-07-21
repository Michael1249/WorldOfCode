#include <QCoreApplication>
#include "UserInterface/interface.h"
#include "UserInterface/userstdcommands.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::API::Run();

    return a.exec();
}
