#include <QCoreApplication>
#include <userinterface.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UserInterface interface;

    return a.exec();
}
