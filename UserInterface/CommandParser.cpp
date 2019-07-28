#include "qiostream.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "CommandParser.h"

namespace UI
{

void CommandParser::addCommand(const Command &pCommand)
{

    if (mCommands.find(pCommand.getName()) != mCommands.end())
    {
        throw QExceptionMessage(ERR_CMD_REDEFINE.arg(pCommand.getName()));
    }

    mCommands.insert(pCommand.getName(), &pCommand);
}

void CommandParser::removeCommand(const Command &pCommand)
{
    mCommands.remove(pCommand.getName());
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
            qio::qout << "[ERROR]:" << ERR_UNCNOWN_CMD << endl;
            qio::qout.flush();
        }

    }

}

const CommandParser::command_map &CommandParser::getCommands() const
{
    return mCommands;
}

CommandParser::command_map CommandParser::getActiveCommands() const
{
    command_map result;
    for(auto command : mCommands)
    {

        if(command->isEnable())
        {
            result.insert(command->getName(), command);
        }

    }
    return result;
}

} // UI
