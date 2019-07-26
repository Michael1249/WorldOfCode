#include <QTextStream>
#include "qiostream.h"
#include "StdCommands.h"
#include "Interface.h"

namespace UI
{

void Run()
{
    static StdCommands std_commands;
    Interface::getInstance().run();
}

void Interface::addCommand(const Command &pCommand)
{
    mParser.addCommand(pCommand);
}

void Interface::removeCommand(const Command &pCommand)
{
    mParser.removeCommand(pCommand);
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

} // UI
