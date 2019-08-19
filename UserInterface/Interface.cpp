#include <QTextStream>
#include "qiostream.h"
#include "StdCommands.h"
#include "UIConstants.h"
#include "Interface.h"

namespace UI
{

void Run()
{
    static StdCommands std_commands;

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:interface"))); // create host node without Registry
    srcNode.enableRemoting(&Interface::getInstance()); // enable remoting/sharing

    Interface::getInstance().run();
}

void Interface::addCommand(const Command& pCommand, const CommandInfo& pInfo)
{
    mParser.addCommand(pCommand,pInfo);
}

void Interface::removeCommand(const QString &pCommand_name)
{
    mParser.removeCommand(pCommand_name);
}

Interface::Interface(QObject *parent): InterfaceSimpleSource (parent)
{
}

Interface& Interface::getInstance()
{
    static Interface* p_instance = new Interface();
    return *p_instance;
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

}

const CommandParser &Interface::getParser()
{
    return mParser;
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
