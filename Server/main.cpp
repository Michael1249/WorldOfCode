#include <QCoreApplication>
#include <qiostream.h>
#include "Server/server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    serverSpace::Server c;
    c.start();

    return a.exec();
}
