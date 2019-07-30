#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "GameTemplate/GameTemplate.h"

namespace ServerSide
{

class Server : public QObject
{
    Q_OBJECT

public:
    Server() = default;

    void start();

private:
    void send_responce();

    GameTemplate* mGame;
};

} // ServerSide

#endif // SERVER_H
