#include <qiostream.h>
#include <QDataStream>
#include "client.h"

using namespace clientSpace;
using namespace QIO;

Client::Client(const QString pHost)
{
    mp_clientSocket = new QTcpSocket(this);

    mp_clientSocket->connectToHost(pHost, 9999);

    connect(mp_clientSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(mp_clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
    connect(mp_clientSocket, SIGNAL(readyRead()), SLOT(slotReadServer()));
}

void Client::slotConnected()
{
    qout << "Connected to server." << endl;
    qout.flush();
}


void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(mp_clientSocket->errorString())
                    );
    qout << strError << endl;
    qout.flush();
}

void Client::slotReadServer()
{
    QDataStream in(mp_clientSocket);

    for(;;)
    {
        if(!mi16_nextBlockSize)
        {
            if(mp_clientSocket->bytesAvailable() < sizeof (quint16)) break;

            in >> mi16_nextBlockSize;
        }

        if(mp_clientSocket->bytesAvailable() < mi16_nextBlockSize) break;

        QString str;

        in >> str;

        mi16_nextBlockSize = 0;

        QIO::qout << "Server send: " << str << endl;
        QIO::qout.flush();
    }

    mp_clientSocket->flush();
}

void Client::sendToServer(const QString str)
{
    mp_clientSocket->flush();
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    mp_clientSocket->write(arrBlock);
}
