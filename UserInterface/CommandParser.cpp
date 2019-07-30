#include "qiostream.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "CommandParser.h"

namespace UI
{

void CommandParser::addCommand(const Command &pCommand)
{

    if (mCommands.find(pCommand.getInfo().getName()) != mCommands.end())
    {
        throw QExceptionMessage(ERR_CMD_REDEFINE.arg(pCommand.getInfo().getName()));
    }

    auto signal = mCommands.insert(pCommand.getInfo().getName(), QPointer<CallCommandSignal>(new CallCommandSignal())).value().data();
    signal->setInfo(pCommand.getInfo());
    QObject::connect(signal, SIGNAL(exec(const QString&)), &pCommand, SLOT(exec_slot(const QString&)));
}

void CommandParser::removeCommand(const Command &pCommand)
{
    mCommands.remove(pCommand.getInfo().getName());
}

void CommandParser::parseString(const QString& pCommand_str)
{
    //TODO: owerwrite with stringview, unnececary init new stings
    QString command_name = pCommand_str.section(" ", 0, 0);
    QString command_args = pCommand_str.section(" ", 1);

    if (command_name != "")
    {
        auto command_iter = mCommands.find(command_name);

        if (command_iter != mCommands.end())
        {
            command_iter.value()->exec(command_args);
        }
        else
        {
            qio::qout << "[ERROR]:" << ERR_UNKNOWN_CMD << endl;
            qio::qout.flush();
        }

    }

}

const CommandParser::command_map &CommandParser::getCommands() const
{
    return mCommands;
}

} // UI
