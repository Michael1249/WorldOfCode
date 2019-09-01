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
    // Init Global service
    addService_slot(GLOBAL_SERVICE_NAME,"");

    // init help request command
    CommandInfo help_request_info;
    help_request_info.setName("help");
    help_request_info.setHelpTip("helps to find command and get discription");
    help_request_info.addArg(
            ArgInfo
            {
                .name="filter",
                .short_name = 'f',
                .help_tip = "search for commands which contain <filter>,\n"
                            "show command's details if it's found."
            }
        );
    addGlobalCommand(this, &LocalInterface::help_cmd, help_request_info);

    // init sync request command
    CommandInfo sync_request_info;
    sync_request_info.setName("sync");
    sync_request_info.setHelpTip("Synchronize data from existing services.");
    addGlobalCommand(this, &LocalInterface::sync_cmd, sync_request_info);

    InputReader* reader = new InputReader();
    reader->moveToThread(&input_thread);
    connect(&input_thread, &QThread::finished, reader, &QObject::deleteLater);
    connect(this, &LocalInterface::listenForInput_signal, reader, &InputReader::listenForInput_slot);
    connect(reader, &InputReader::newLineDetected_signal, this, &LocalInterface::processCommand_slot);
    input_thread.start();

    // init remoting
    //TODO url should be overwrited with IP
    QUrl url = QUrl(QStringLiteral("local:interface"));
    mHost_node = new QRemoteObjectHost(url, this);
    mHost_node->enableRemoting(this); // enable remoting/sharing
    QTimer::singleShot(0, this, SLOT(run_slot()));
    QObject::connect(this, SIGNAL(finished_signal()), pApp, SLOT(quit()));
}

void LocalInterface::addService(ServiceBase* pServise)
{
    addService_slot(pServise->getName(), pServise->getHelpTip());
}

void LocalInterface::addExistCommand(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo)
{
    // TODO: overwrite this shit
    auto service_iter = mServices.find(pService_name);

    if(service_iter != mServices.end())
    {
        qio::qout << CMD_INIT_MSG << pInfo.getName() << endl;
        auto command_rep = service_iter.value()->addCommand(pInfo);
        QObject::connect(command_rep, SIGNAL(exec_signal(const QVector<QString>&)), &pCommand, SLOT(exec_slot(const QVector<QString>&)));
        QObject::connect(&pCommand, SIGNAL(destroyed()), command_rep, SLOT(commandDestroyed_slot()));
        QObject::connect(this, &LocalInterface::synchronize_signal, &pCommand, [this, &pCommand, &pService_name]()
        {
            auto service_iter = mServices.find(pService_name);

            if(service_iter != mServices.end())
            {
                qio::qout << CMD_INIT_MSG << pCommand.getInfo().getName() << endl;
                auto command_rep = service_iter.value()->addCommand(pCommand.getInfo());
                QObject::connect(command_rep, SIGNAL(exec_signal(const QVector<QString>&)), &pCommand, SLOT(exec_slot(const QVector<QString>&)));
                QObject::connect(&pCommand, SIGNAL(destroyed()), command_rep, SLOT(commandDestroyed_slot()));
            }
            else
            {
                // TODO: exception or ???
            }
        });
    }
    else
    {
        // TODO: exception or ???
    }

}

void LocalInterface::addRemoteCommand_slot(const QString& pService_name, const QByteArray &pInfo)
{
    auto service_iter = mServices.find(pService_name);

    if(service_iter != mServices.end())
    {
        CommandInfo command_info(pInfo);
        qio::qout << CMD_INIT_MSG << command_info.getName() << endl;
        auto command_rep = service_iter.value()->addCommand(pInfo);
        mHost_node->enableRemoting(command_rep, "interface/" + pService_name + "/" + command_info.getName());
    }
    else
    {

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
    if (!mServices.contains(pName))
    {
         mServices.insert(pName, QPointer<ServiceRepresent>(new ServiceRepresent(pName, pHelp_tip)));
    }
}

void LocalInterface::removeService_slot(const QString &pName)
{
    mServices.remove(pName);
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
            service_iter.value()->processCommand(command_line);
        }
        else
        {
            mServices.begin().value()->processCommand(line);
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
    emit synchronize_signal();
}

void InputReader::listenForInput_slot()
{
    emit newLineDetected_signal(qio::qin.readLine());
}

} // UI
