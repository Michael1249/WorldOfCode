#include <QCoreApplication>
#include "UserInterface/Interface.h"
#include "uiconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::Run();

    return a.exec();
}
