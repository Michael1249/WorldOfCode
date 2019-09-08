#include <QTextStream>
#include "qiostream.h"
#include <QTimer>
#include "UIConstants.h"
#include "LocalInterface.h"
#include "ServiceBase.h"

namespace UI
{

LocalInterface::LocalInterface(QCoreApplication *pApp):
    InterfaceSimpleSource (pApp)
{

    InputReader* reader = new InputReader();
    reader->moveToThread(&input_thread);
    connect(&input_thread, &QThread::finished, reader, &QObject::deleteLater);
    connect(this, &LocalInterface::listenForInput_signal, reader, &InputReader::listenForInput_slot);
    connect(reader, &InputReader::newLineDetected_signal, this, &LocalInterface::processCommand_slot);
    input_thread.start();

    init_remoting();

    QObject::connect(this, SIGNAL(finished_signal()), pApp, SLOT(quit()));

    mGlobal_service.reset(new GlobalService(this));
}

void LocalInterface::connectSyncSignal(ServiceBase* pServise)
{
    QObject::connect(this, &LocalInterface::synchronize_signal, pServise, [this, pServise]()
    {
        addService_slot(pServise->getName(), pServise->getHelpTip());
    });
}

void LocalInterface::connectSyncSignal(Command *pCommand)
{
    QObject::connect(this, &LocalInterface::synchronize_signal, pCommand, [this, pCommand]()
    {
        addExistCommand(pCommand);
    });
}


void LocalInterface::addExistCommand(Command* pCommand)
{
    auto service_iter = mService_represents.find(pCommand->getServiceName());

    if(service_iter != mService_represents.end())
    {
        auto command_rep = service_iter->second.get()->addCommand(pCommand->getInfo());

        if(command_rep)
        {
            QObject::connect(command_rep, SIGNAL(exec_signal(const QVector<QString>&)), pCommand, SLOT(exec_slot(const QVector<QString>&)));
            QObject::connect(pCommand, SIGNAL(destroyed_signal()), command_rep, SLOT(commandDestroyed_slot()));
        }

    }
    else
    {
        qio::qout << "[ERROR]: Can not add command '" + pCommand->getInfo().getName() +
                    "' to service '" + pCommand->getServiceName() + "'. Service does not exist!" << endl;
    }

}

void LocalInterface::addRemoteCommand_slot(const QString& pService_name, const QByteArray &pInfo)
{
    auto service_iter = mService_represents.find(pService_name);
    CommandInfo command_info(pInfo);

    if(service_iter != mService_represents.end())
    {
        auto command_rep = service_iter->second.get()->addCommand(pInfo);

        if(command_rep)
        {
            mHost_node->enableRemoting(command_rep, "interface/" + pService_name + "/" + command_info.getName());
            QObject::connect(command_rep, SIGNAL(destroyed(QObject*)), this, SLOT(disableRemoting(QObject*)));
        }

    }
    else
    {
        qio::qout << "[ERROR]: Can not add command '" + command_info.getName() +
                    "' to service '" + pService_name + "'. Service does not exist!" << endl;
    }

}


LocalInterface::~LocalInterface()
{
    input_thread.quit();
    input_thread.wait();
}

void LocalInterface::listenForInput()
{
    qio::qout << DEFAULT_INPUT << flush;
    emit listenForInput_signal();
}

void LocalInterface::addService_slot(const QString &pName, const QString& pHelp_tip)
{
    if (mService_represents.find(pName) == mService_represents.end())
    {
         qio::qout << SERVICE_ADDED_MSG << pName << endl;
         mService_represents.emplace(pName, std::make_unique<ServiceRepresent>(pName, pHelp_tip));
    }
    else
    {
        qio::qout << "[ERROR]: Can not add service '" + pName +
                     "'. This service allready exists." << endl;
    }
}

void LocalInterface::removeService_slot(const QString &pName)
{
    if (mService_represents.find(pName) != mService_represents.end())
    {
        qio::qout << SERVICE_REMOVED_MSG << pName << endl;
        mService_represents.erase(pName);
    }
    else
    {
        qio::qout << "[ERROR]: Can not remove service '" + pName +
                     "'. This service allready removed." << endl;
    }

}

void LocalInterface::disableRemoting(QObject *pObj)
{
    mHost_node->disableRemoting(pObj);
}

void LocalInterface::run_slot()
{
    listenForInput();
}

void LocalInterface::processCommand_slot(const QString &line)
{
    QString service_name = line.section(" ", 0, 0);
    QString command_line = line.section(" ", 1);

    if(service_name != "")
    {
        auto service_iter = mService_represents.find(service_name);

        if(service_iter != mService_represents.end())
        {
            service_iter->second->processCommand(command_line);
        }
        else
        {
            mService_represents.begin()->second->processCommand(line);
        }

    }

    if(mFlag_run_end)
    {
        emit finished_signal();
    }
    else
    {
        listenForInput();
    }
}

void LocalInterface::sync()
{
    mService_represents.clear();
    emit synchronize_signal();
}

void LocalInterface::quit()
{
    emit finished_signal();
}

void LocalInterface::init_remoting()
{
    //TODO url should be overwrited with IP
    QUrl url = QUrl(QStringLiteral("local:interface"));
    mHost_node = new QRemoteObjectHost(url, this);
    mHost_node->enableRemoting(this); // enable remoting/sharing
    QTimer::singleShot(0, this, SLOT(run_slot()));
}

void InputReader::listenForInput_slot()
{
    emit newLineDetected_signal(qio::qin.readLine());
}

} // UI
