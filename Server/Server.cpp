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

}

Server::~Server()
{
}



