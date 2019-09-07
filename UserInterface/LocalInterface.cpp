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
    init_global_service();
    init_help_cmd();
    init_sync_cmd();
    init_quit_cmd();

    InputReader* reader = new InputReader();
    reader->moveToThread(&input_thread);
    connect(&input_thread, &QThread::finished, reader, &QObject::deleteLater);
    connect(this, &LocalInterface::listenForInput_signal, reader, &InputReader::listenForInput_slot);
    connect(reader, &InputReader::newLineDetected_signal, this, &LocalInterface::processCommand_slot);
    input_thread.start();

    init_remoting();

    QObject::connect(this, SIGNAL(finished_signal()), pApp, SLOT(quit()));
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
    auto service_iter = mServices.find(pCommand->getServiceName());

    if(service_iter != mServices.end())
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
    auto service_iter = mServices.find(pService_name);
    CommandInfo command_info(pInfo);

    if(service_iter != mServices.end())
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
    if (mServices.find(pName) == mServices.end())
    {
         qio::qout << SERVICE_ADDED_MSG << pName << endl;
         mServices.emplace(pName, std::make_unique<ServiceRepresent>(pName, pHelp_tip));
    }
    else
    {
        qio::qout << "[ERROR]: Can not add service '" + pName +
                     "'. This service allready exists." << endl;
    }
}

void LocalInterface::removeService_slot(const QString &pName)
{
    if (mServices.find(pName) != mServices.end())
    {
        qio::qout << SERVICE_REMOVED_MSG << pName << endl;
        mServices.erase(pName);
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
        auto service_iter = mServices.find(service_name);

        if(service_iter != mServices.end())
        {
            service_iter->second->processCommand(command_line);
        }
        else
        {
            mServices.begin()->second->processCommand(line);
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

void LocalInterface::help_cmd(const QString &pStr)
{
//    auto command_map = mServices.getCommands();

//    for(auto iter = command_map.begin(); iter != command_map.end();)
//    {
//        if(!iter.value()->getInfo().getName().contains(pStr, Qt::CaseInsensitive))
//        {
//            iter = command_map.erase(iter);
//        }
//        else
//        {
//            ++iter;
//        }
//    }

//    if (command_map.size() == 0)
//    {
//        qio::qout << NOTHING_FOUND_MSG << endl;
//    }
//    else if(command_map.size() == 1)
//    {
//        auto command = command_map.begin().value();
//        qio::qout << command->getInfo().getName();

//        for (auto& arg: command->getInfo().getArgumentsInfo())
//        {
//            qio::qout << QString(" <%1>").arg(arg.name);
//        }

//        qio::qout << endl;

//        if(command->getInfo().hasHelpTip())
//        {
//            qio::qout << command->getInfo().getHelpTip() << endl;
//        }

//        if(command->getInfo().getArgumentsInfo().size())
//        {
//            qio::qout << left;

//            for (auto& arg: command->getInfo().getArgumentsInfo())
//            {
//                qio::qout << QString(40, '_')
//                          << endl
//                          << QString("<%1, %2> = \"%3\"")
//                             .arg(arg.name)
//                             .arg(arg.short_name)
//                             .arg(arg.default_value)
//                          << endl
//                          << arg.help_tip
//                          << endl;
//            }

//        }
//        else
//        {
//            qio::qout << WITHOUT_ARGUMENTS_MSG << endl;
//        }

//    }
//    else
//    {
//        for(auto command : command_map)
//        {
//            qio::qout << qSetFieldWidth(16)
//                      << left
//                      << command->getInfo().getName();
//            if(command->getInfo().hasHelpTip())
//            {
//                qio::qout << qSetFieldWidth(0)
//                          << " : "
//                          << command->getInfo().getHelpTip();
//            }
//            qio::qout << endl;
//        }
//    }

    //  qio::qout.flush();
}

void LocalInterface::sync_cmd()
{
    mServices.clear();
    init_global_service();
    emit synchronize_signal();
}

void LocalInterface::quit_cmd()
{
    emit finished_signal();
}

void LocalInterface::init_global_service()
{
    addService_slot(GLOBAL_SERVICE_NAME, GLOBAL_SERVICE_HELP_TIP);
}

void LocalInterface::init_help_cmd()
{
    CommandInfo info;
    info.setName("help");
    info.setHelpTip("helps to find command and get discription");
    info.addArg(
            ArgInfo
            {
                .name="filter",
                .short_name = 'f',
                .help_tip = "search for commands which contain <filter>,\n"
                            "show command's details if it's found."
            }
        );
    addGlobalCommand(this, &LocalInterface::help_cmd, info);
}

void LocalInterface::init_sync_cmd()
{
    CommandInfo info;
    info.setName("sync");
    info.setHelpTip("Synchronize data from existing services.");
    addGlobalCommand(this, &LocalInterface::sync_cmd, info);
}

void LocalInterface::init_quit_cmd()
{
    CommandInfo info;
    info.setName("quit");
    info.setHelpTip("Quit the terminal.");
    addGlobalCommand(this, &LocalInterface::quit_cmd, info);
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
