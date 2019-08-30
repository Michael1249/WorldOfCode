#include <QCoreApplication>
#include <QTimer>
#include "RemoteInterface.h"
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    auto mReplica_node = new QRemoteObjectNode(); // create remote object node
//    mReplica_node->connectToNode(QUrl(QStringLiteral("local:interface"))); // connect with remote host node

//    auto rep = mReplica_node->acquire<InterfaceReplica>(); // acquire replica of source from host node

//    auto stateChangeTimer = new QTimer(); // Initialize timer
//    QObject::connect(stateChangeTimer, SIGNAL(timeout()), rep , SLOT(test())); // connect timeout() signal from stateChangeTimer to timeout_slot() of simpleSwitch
//    stateChangeTimer->start(2000);


    UI::RemoteInterface interface(QUrl(QStringLiteral("local:interface")));

    Worker worker1(&interface, "Martin");

    Worker worker2(&interface, "Roy");

    return a.exec();
}
