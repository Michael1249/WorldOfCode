#include "client.h"
#include <qiostream.h>

using namespace  clientSpace;

Client::Client(const QString pHost, quint16 pPort)
{
    mptrSocket = new QTcpSocket;

    mptrSocket->connectToHost(pHost, pPort);

    connect(mptrSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(mptrSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(mptrSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    if(!mptrSocket->isOpen())
    {
        qio::qout << "Connection is close." << endl;
    }
}

void Client::slotReadyRead()
{
    QDataStream in(mptrSocket);
    for (;;)
    {
        if(!mNextBlockSize)
        {
            if(mptrSocket->bytesAvailable() < sizeof (quint16))
            {
                break;
            }
            in >> mNextBlockSize;
        }

        if(mptrSocket->bytesAvailable() < mNextBlockSize) {
            break;
        }

        QTime time;
        QString str;
        in >> time >> str;

        qio::qout << "Data read succesfully." << endl;
        mNextBlockSize = 0;
    }
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
                     QString(mptrSocket->errorString())
                    );
    qio::qout << strError << endl;
}

void Client::slotSendToServer() {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out << quint16(0) << QTime::currentTime() << "Vlad";

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof (quint16));

    mptrSocket->write(arrBlock);
}

void Client::slotConnected() {
    qio::qout << "Connection is open." << endl;
}
