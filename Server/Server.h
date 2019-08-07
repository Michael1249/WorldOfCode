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

    void lounch_game(const QString& pGame_name);
    void close_game();

    void print(const QString& pStr);
    QString read();
    QString read_err();

    QProcess::ProcessState getState();

public slots:
    void readyToReadStdOutput();
    void readyToReadErrOutput();

private:
    QStringList getExistingGames();

    QProcess* mGame_procces;
    QDir mGames_dir;
};


#endif // SERVER_H
