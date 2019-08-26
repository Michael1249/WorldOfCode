#include <QTextStream>
#include "qiostream.h"
#include <QTimer>
#include "UIConstants.h"
#include "LocalInterface.h"

namespace UI
{

LocalInterface::LocalInterface(QCoreApplication *parent):
    InterfaceSimpleSource (parent)
{
    // init help request command
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
    mHelp_request_cmd.link_to(this, &LocalInterface::help_request);
    addCommand_slot(mHelp_request_cmd, info);

    InputReader* reader = new InputReader();
    reader->moveToThread(&input_thread);
    connect(&input_thread, &QThread::finished, reader, &QObject::deleteLater);
    connect(this, &LocalInterface::listenForInput_signal, reader, &InputReader::listenForInput_slot);
    connect(reader, &InputReader::newLineDetected_signal, this, &LocalInterface::processLine_slot);
    input_thread.start();

    // init remoting
    QUrl url = QUrl(QStringLiteral("local:interface"));
    mHost_node = new QRemoteObjectHost(url, this);
    mHost_node->enableRemoting(this); // enable remoting/sharing
    QTimer::singleShot(0, this, SLOT(run_slot()));
    QObject::connect(this, SIGNAL(finished_signal()), parent, SLOT(quit()));
}

void LocalInterface::addCommand_slot(Command& pCommand, const CommandInfo& pInfo)
{
    qio::qout << CMD_INIT_MSG << pInfo.getName() << endl;
    auto command_rep = mParser.addCommand(pInfo);
    QObject::connect(command_rep, SIGNAL(exec_signal(const QVector<QString>&)), &pCommand, SLOT(exec_slot(const QVector<QString>&)));
    QObject::connect(command_rep, SIGNAL(destroyed(const QString&)), this, SLOT(removeCommand_slot(const QString&)));
    QObject::connect(&pCommand, SIGNAL(destroyed()), command_rep, SLOT(commandDestroyed_slot()));
}

void LocalInterface::addRemoteCommand_slot(const QByteArray &pInfo)
{
    CommandInfo command_info(pInfo);
    qio::qout << CMD_INIT_MSG << command_info.getName() << endl;
    auto command_rep = mParser.addCommand(command_info);
    QObject::connect(command_rep, SIGNAL(destroyed(const QString&)), this, SLOT(removeCommand_slot(const QString&)));
    mHost_node->enableRemoting(command_rep, "interface/" + command_info.getName());
}

void LocalInterface::removeCommand_slot(const QString &pCommand_name)
{
    qio::qout << CMD_EXIT_MSG << pCommand_name << endl;
    qio::qout << pCommand_name << endl;
    mParser.removeCommand(pCommand_name);
}

void LocalInterface::test()
{
    qio::qout<< "QQQQ" << endl;
}

LocalInterface::~LocalInterface()
{
    input_thread.quit();
    input_thread.wait();
}

void LocalInterface::listenForInput()
{
    qio::qout << DEFAULT_INPUT;
    qio::qout.flush();
    emit listenForInput_signal();
}

void LocalInterface::run_slot()
{
    listenForInput();
}

void LocalInterface::processLine_slot(const QString &line)
{
    mParser.parseString(line);
    if(mFlag_run_end)
    {
        emit finished_signal();
    }
    else
    {
        listenForInput();
    }
}

void LocalInterface::help_request(const QString &pStr)
{
    auto command_map = mParser.getCommands();

    for(auto iter = command_map.begin(); iter != command_map.end();)
    {
        if(!iter.value()->getInfo().getName().contains(pStr, Qt::CaseInsensitive))
        {
            iter = command_map.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    if (command_map.size() == 0)
    {
        qio::qout << NOTHING_FOUND_MSG << endl;
    }
    else if(command_map.size() == 1)
    {
        auto command = command_map.begin().value();
        qio::qout << command->getInfo().getName();

        for (auto& arg: command->getInfo().getArgumentsInfo())
        {
            qio::qout << QString(" <%1>").arg(arg.name);
        }

        qio::qout << endl;

        if(command->getInfo().hasHelpTip())
        {
            qio::qout << command->getInfo().getHelpTip() << endl;
        }

        if(command->getInfo().getArgumentsInfo().size())
        {
            qio::qout << left;

            for (auto& arg: command->getInfo().getArgumentsInfo())
            {
                qio::qout << QString(40, '_')
                          << endl
                          << QString("<%1, %2> = \"%3\"")
                             .arg(arg.name)
                             .arg(arg.short_name)
                             .arg(arg.default_value)
                          << endl
                          << arg.help_tip
                          << endl;
            }

        }
        else
        {
            qio::qout << WITHOUT_ARGUMENTS_MSG << endl;
        }

    }
    else
    {
        for(auto command : command_map)
        {
            qio::qout << qSetFieldWidth(16)
                      << left
                      << command->getInfo().getName();
            if(command->getInfo().hasHelpTip())
            {
                qio::qout << qSetFieldWidth(0)
                          << " : "
                          << command->getInfo().getHelpTip();
            }
            qio::qout << endl;
        }
    }

  qio::qout.flush();
}

void InputReader::listenForInput_slot()
{
    emit newLineDetected_signal(qio::qin.readLine());
}

} // UI
