#include "server.h"
#include "qiostream.h"

void foo()
{
    QIO::qout << "AAA";
    QIO::qout.flush();
}

Server::Server()
{
    foo();
}
