#include <QFileInfo>
#include <QDir>
#include "Server.h"
#include "qiostream.h"
#include "qexceptionmessage.h"

Server::Server():
      mGames_dir(QDir(QCoreApplication::applicationDirPath() + "/Games"))
{

}

QStringList Server::getExistingGames()
{
    QStringList result = mGames_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    QMutableListIterator<QString> i(result);

    while (i.hasNext())
    {
        auto& current_folder = i.next();
        if (!QFileInfo::exists(mGames_dir.path() + '/' + current_folder + '/' + current_folder + ".exe"))
            i.remove();
    }

    return result;
}

void Server::launch_game(const QString &pGame_name)
{
    mGame_process->start("../Games/" + pGame_name);
    if(!mGame_process->waitForStarted())
        qio::qout << "Server can not start game " << pGame_name << endl;

    QObject::connect(mGame_process, SIGNAL(readyReadStandardOutput(QPrivateSignal)), this, SIGNAL(readyReadStd()), Qt::QueuedConnection);
    QObject::connect(mGame_process, SIGNAL(readyReadStandardError(QPrivateSignal)), this, SIGNAL(readyReadErr()), Qt::QueuedConnection);
}

void Server::print(const QString &pStr)
{
    mGame_process->write(pStr.toUtf8());
}

QString Server::readStd()
{
    return mGame_process->readAllStandardOutput();
}

QString Server::readErr()
{
    return mGame_process->readAllStandardError();
}

QProcess::ProcessState Server::getState()
{
    return mGame_process->state();

}

void Server::close_game()
{
    mGame_process->terminate();
}

Server::~Server()
{
}



