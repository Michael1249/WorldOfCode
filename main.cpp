#include <QCoreApplication>
#include "UserInterface/Interface.h"
#include "UserInterface/UITest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::Run();

    return a.exec();
}
