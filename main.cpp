#include <QCoreApplication>
#include "UserInterface/interface.h"
#include <qiostream.h>
#include <functional>

class A
{
public:
    void foo(QString a, QString b, QString c)
    {
        QIO::qout << a << '\n'
                  << b << '\n'
                  << c << '\n';
        QIO::qout.flush();
    }
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UserInterface::Interface::getInstance()->run();

    return a.exec();
}
