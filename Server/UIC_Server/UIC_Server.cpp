#include "UIC_Server.h"
#include "qiostream.h"
#include "qexceptionmessage.h"

UIC_Server::UIC_Server()
{
    mServer_Process = new QProcess();
    mServer_Process->start(SERVER_PATH);

    qio::qout << "Starting process \"Server\"..." << endl;

    if(!mServer_Process->waitForStarted())
    {
        throw QExceptionMessage("Process \"Server\" isn't started!");
    }

    mServer_Process->write("hello\n");
    qio::qout << "Waiting for responce..." << endl;

    if(!mServer_Process->waitForReadyRead())
    {
        throw QExceptionMessage("Process \"Server\" no responce!");
    }

    QString responce = mServer_Process->readAllStandardOutput();

    if (!responce.startsWith("hello"))
    {
        throw QExceptionMessage("'" + responce + "'");
    }
    else
    {
        qio::qout << "The Server has started." << endl;
    }

}

UIC_Server::~UIC_Server()
{
    mServer_Process->close();

    qio::qout << "Waiting for finishing..." << endl;

    if(!mServer_Process->waitForFinished())
    {
        mServer_Process->kill();
    }

    qio::qout << "The Server has closed." << endl;

    delete mServer_Process;
}
