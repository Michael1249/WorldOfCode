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
    virtual void addService(ServiceBase* pServise);
    virtual void addExistCommand(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo);
    QRemoteObjectNode* mReplica_node;
    QSharedPointer<InterfaceReplica> mReplica;
};

} // UI

#endif // REMOTEINTERFACE_H
