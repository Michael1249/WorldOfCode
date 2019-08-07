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

