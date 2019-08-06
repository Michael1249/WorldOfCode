#include <QFileInfo>
#include <QDir>
#include "Server.h"
#include "qiostream.h"
#include "qexceptionmessage.h"

Server::Server():
      mGames_dir(QDir(QCoreApplication::applicationDirPath() + "/Games"))
{
      mShowExistingGames_cmd
              .setName("games")
              .link_to(this, &Server::showExistingGames)
              .setHelpTip("Show list of existing games.")
              .addToUI();

//    mServer_Process = new QProcess();
//    mServer_Process->start(SERVER_PATH);

//    qio::qout << "Starting process \"Server\"..." << endl;

//    if(!mServer_Process->waitForStarted())
//    {
//        throw QExceptionMessage("Process \"Server\" isn't started!");
//    }

//    mServer_Process->write("hello\n");
//    qio::qout << "Waiting for responce..." << endl;

//    if(!mServer_Process->waitForReadyRead())
//    {
//        throw QExceptionMessage("Process \"Server\" no responce!");
//    }

//    QString responce = mServer_Process->readAllStandardOutput();

//    if (!responce.startsWith("hello"))
//    {
//        throw QExceptionMessage("'" + responce + "'");
//    }
//    else
//    {
//        qio::qout << "The Server has started." << endl;
//    }

}

Server::~Server()
{
//    mServer_Process->close();

//    qio::qout << "Waiting for finishing..." << endl;

//    if(!mServer_Process->waitForFinished())
//    {
//        mServer_Process->kill();
//    }

//    qio::qout << "The Server has closed." << endl;

    //    delete mServer_Process;
}

void Server::showExistingGames()
{
    for (auto& game_name  : getExistingGames())
    {
        qio::qout << game_name << endl;
    }
}

void Server::lounch(const QString &pGame_name)
{
    QString game_path = mGames_dir.path() + '/' + pGame_name + '/' + pGame_name + ".exe";

    if (QFileInfo::exists(game_path))
    {
        mGame_procces = new QProcess();
        mGame_procces->start(game_path);
        qio::qout << "Game started!" << endl;
    }
    else
    {
        qio::qout << QString("Can not find game with name \"%1\"!").arg(pGame_name) << endl;
    }

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

