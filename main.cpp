#include <QCoreApplication>
#include "UserInterface/Interface.h"
#include "UIConfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setUpUI();
    UI::Run();

    return a.exec();
}
