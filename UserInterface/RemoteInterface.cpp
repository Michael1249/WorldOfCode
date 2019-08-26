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

UI::RemoteInterface::~RemoteInterface()
{
}

void UI::RemoteInterface::addCommand_slot(UI::Command &pCommand, const UI::CommandInfo &pInfo)
{
    QTimer::singleShot(0, [this, &pCommand, pInfo]()
    {
        mReplica->waitForSource();
        mReplica->addRemoteCommand_slot(QJsonDocument(pInfo.toJson()).toJson());
        auto command_rep = mReplica_node->acquire<CommandRepresentReplica>("interface/" + pInfo.getName());
        command_rep->setParent(&pCommand);
        QObject::connect(command_rep, SIGNAL(exec_signal(const QVector<QString>&)), &pCommand, SLOT(exec_slot(const QVector<QString>&)));
        QObject::connect(&pCommand, SIGNAL(destroyed()), command_rep, SLOT(commandDestroyed_slot()));
    });

}

void UI::RemoteInterface::removeCommand_slot(const QString &pCommand_name)
{
    mReplica->removeCommand_slot(pCommand_name);
}
