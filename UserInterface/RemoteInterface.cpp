#include <Qtimer>
#include <QJsonObject>
#include <QJsonDocument>
#include "RemoteInterface.h"
#include "CommandRepresent_replica.h"

UI::RemoteInterface::RemoteInterface(const QUrl &pUrl)
{
    mReplica_node = new QRemoteObjectNode(this); // create remote object node
    mReplica_node->connectToNode(pUrl); // connect with remote host node

    mReplica.reset(mReplica_node->acquire<InterfaceReplica>()); // acquire replica of source from host node
}


void UI::RemoteInterface::addCommand_slot(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo)
{
    QTimer::singleShot(0, [this, pService_name, &pCommand, pInfo]()
    {
        mReplica->waitForSource();
        mReplica->addRemoteCommand_slot(pService_name, QJsonDocument(pInfo.toJson()).toJson());

        auto command_rep = mReplica_node->acquire<CommandRepresentReplica>("interface/" + pService_name + "/" + pInfo.getName());
        command_rep->setParent(&pCommand);

        QObject::connect(command_rep, SIGNAL(exec_signal(const QVector<QString>&)), &pCommand, SLOT(exec_slot(const QVector<QString>&)));
        QObject::connect(&pCommand, SIGNAL(destroyed()), command_rep, SLOT(commandDestroyed_slot()));
    });

}

void UI::RemoteInterface::addService_slot(const QString &pName, const QString &pHelp_tip)
{
    mReplica->addService_slot(pName, pHelp_tip);
}

void UI::RemoteInterface::removeService_slot(const QString &pName)
{
    mReplica->removeService_slot(pName);
}

