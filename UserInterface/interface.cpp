#include <QTextStream>
#include "qiostream.h"
#include "userstdcommands.h"
#include "interface.h"

namespace UI
{
namespace User
{

void Interface::addCommand(const Command &pCommand)
{
    mParser.addCommand(pCommand);
}

void Interface::removeCommand(const Command &pCommand)
{
    mParser.removeCommand(pCommand);
}

Interface *Interface::getInstance()
{
    static Interface* p_instance = new Interface();
    return p_instance;
}

void Interface::run()
{
    using namespace QIO;
    while (!mFlag_run_end)
    {
        qout << ">>>";
        qout.flush();

        QString args_str = qin.readLine();

        mParser.parseString(args_str);
    }

}

const CommandParser &Interface::getParser()
{
    return mParser;
}

void Run()
{
    static UserStdCommands std_commands;
    Interface::getInstance()->run();
}

} // API
} // UI
