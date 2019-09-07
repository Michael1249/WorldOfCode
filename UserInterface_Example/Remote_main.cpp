#include <QCoreApplication>
#include <QTimer>
#include "RemoteInterface.h"
#include "slaves.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::RemoteInterface interface(QUrl(QStringLiteral("local:interface")));

    Slaves your_slaves(&interface, "your_slaves");

    return a.exec();
}
