#ifndef REMOTEINTERFACE_H
#define REMOTEINTERFACE_H

#include "InterfaceBase.h"
#include "Interface_replica.h"
#include "Command.h"

namespace UI
{

class RemoteInterface :public QObject, public InterfaceBase
{
    Q_OBJECT

public:
    RemoteInterface(const QUrl& pUrl);
    ~RemoteInterface();

public slots:
    virtual void addCommand_slot(Command& pCommand, const CommandInfo& pInfo);
    virtual void removeCommand_slot(const QString &pCommand_name);

private:
    QRemoteObjectNode* mReplica_node;
    QSharedPointer<InterfaceReplica> mReplica;
};

} // UI

#endif // REMOTEINTERFACE_H
