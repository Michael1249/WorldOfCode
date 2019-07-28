#include <QCoreApplication>
#include <Client/client.h>
#include <qiostream.h>

// Send data in little packages
// Must open file in any mode
using namespace QIO;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    clientSpace::Client c("localhost");

    QFile file("test.txt");
//    c.sendToServer(&file);
    c.sendToServer("Vlad");

    return a.exec();
}
