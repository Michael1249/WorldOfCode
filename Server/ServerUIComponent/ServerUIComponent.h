#ifndef UIC_SERVER_H
#define UIC_SERVER_H

#include <QProcess>
//#include "Command.h"

namespace
{

const QString SERVER_PATH = "Server/Server";

}

class ServerUIComponent
{
public:
    ServerUIComponent();
    ~ServerUIComponent();

private:
    QProcess* mServer_Process;
};


#endif // UIC_SERVER_H
