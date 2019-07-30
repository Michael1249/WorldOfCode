#include "qiostream.h"
#include "Server.h"

namespace ServerSide
{

void Server::start()
{
    //init code
    send_responce();
}

void Server::send_responce()
{
    //Server start verification
    QString input;
    qio::qin >> input;
    qio::qout << input << endl;
}

} // ServerSide
