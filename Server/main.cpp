#include <QCoreApplication>
#include <qiostream.h>
#include "ServerClass/server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server c;
    return a.exec();
}
