#include <QCoreApplication>
#include <qiostream.h>
#include "Server/server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    serverSpace::Server c(2323);
    return a.exec();
}
