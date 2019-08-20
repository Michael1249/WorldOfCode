#include <QTextStream>
#include "qiostream.h"
#include <QTimer>
#include "UIConstants.h"
#include "Interface.h"

namespace UI
{

void Interface::addCommand(const Command& pCommand, const CommandInfo& pInfo)
{
    mParser.addCommand(pCommand,pInfo);
}

void Interface::removeCommand(const QString &pCommand_name)
{
    mParser.removeCommand(pCommand_name);
}

Interface::Interface(QCoreApplication *parent):
    InterfaceSimpleSource (parent),
    mRemote_node(QUrl(QStringLiteral("local:interface")))
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
    mHelp_request_cmd.link_to(this, &Interface::help_request);
    mHelp_request_cmd.addToUI(info);

    mRemote_node.enableRemoting(this); // enable remoting/sharing
    QTimer::singleShot(0, this, SLOT(run()));
    QObject::connect(this, SIGNAL(finished()), parent, SLOT(quit()));
}

void Interface::run()
{
    using namespace qio;
    while (!mFlag_run_end)
    {
        qout << DEFAULT_INPUT;
        qout.flush();

        QString args_str = qin.readLine();

        mParser.parseString(args_str);
    }
    emit finished();
}

void Interface::help_request(const QString &pStr)
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

void Interface::addCommand_slot(QString pURL)
{
    qio::qout << "+" + pURL;
}

void Interface::rmCommand_slot(QString pURL)
{
    qio::qout << "-" + pURL;
}

} // UI
