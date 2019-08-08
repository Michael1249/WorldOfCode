#ifndef SERVER_H
#define SERVER_H

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include "Command.h"

class Server
{
public:
    Server();
    ~Server();

    void launch_game(const QString& pGame_name);
    void close_game();

    void print(const QString& pStr);
    QString readStd();
    QString readErr();

    QProcess::ProcessState getState();

signals:
    void readyReadStd();
    void readyReadErr();

private:
    QStringList getExistingGames();

    QProcess* mGame_procces;
    QDir mGames_dir;
};


#endif // SERVER_H
