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

private slots:
    virtual void addService_slot(const QString& pName, const QString& pHelp_tip);
    virtual void removeService_slot(const QString& pName);
    void sync();

private:
    virtual void connectSyncSignal(ServiceBase* pServise);
    virtual void connectSyncSignal(Command* pCommand);
    virtual void addExistCommand(Command* pCommand);
    QRemoteObjectNode* mReplica_node;
    QSharedPointer<InterfaceReplica> mReplica;
};

} // UI

#endif // REMOTEINTERFACE_H
