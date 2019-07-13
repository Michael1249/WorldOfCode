#include <QCoreApplication>
#include "Client/client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    clientSpace::Client c("localhost", 2323);

    return a.exec();
}
