#include <QCoreApplication>
#include <Client/client.h>
#include <qiostream.h>
#include <QFile>

// Send data in little packages
// Must open file in any mode

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    using namespace QIO;

    clientSpace::Client c("localhost");

    return a.exec();
}
