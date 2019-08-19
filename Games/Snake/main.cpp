#include <QCoreApplication>
#include "Interface_replica.h"
#include "qiostream.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSharedPointer<InterfaceReplica> ptr; // shared pointer to hold source replica

    QRemoteObjectNode repNode; // create remote object node
    repNode.connectToNode(QUrl(QStringLiteral("local:interface"))); // connect with remote host node

    ptr.reset(repNode.acquire<InterfaceReplica>()); // acquire replica of source from host node

    ptr.data()->addCommand_slot("QQQ");
    ptr.data()->rmCommand_slot("QQQ");
    qio::qout << "QQQ" << endl;

    return a.exec();
}
