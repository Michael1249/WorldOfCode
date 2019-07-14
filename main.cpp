#include <QCoreApplication>
#include "UserInterface/interface.h"
#include "UserInterface/usercommand.h"
#include "UserInterface/commandadapter.h"
#include <QString>
#include <QtDebug>

struct A
{
    void foo(QString a)
    {
        qInfo() << __FUNCTION__ << ' ' << a;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    A x;

    UserInterface::UserCommand command("test","",{}, UserInterface::getCommandDelegate(x, &A::foo));

    UserInterface::Interface::getInstance()->run();

    return a.exec();
}
