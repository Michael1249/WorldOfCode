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

    void showExistingGames();
    void lounch(const QString& pGame_name);
    void print(const QString& pStr);
    void getStatus();
    void showStatus();
    void close_game();

private slots:
    void game_responce();

private:
    QStringList getExistingGames();

    UI::Command mShowExistingGames_cmd;

    QProcess* mGame_procces;
    QDir mGames_dir;
};


#endif // SERVER_H
