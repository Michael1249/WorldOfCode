#include "qiostream.h"
#include "commandparser.h"

void UI::CommandParser::addCommand(const User::Command &pCommand)
{
    mCommands.insert(pCommand.getName(), &pCommand);
}

void UI::CommandParser::removeCommand(const User::Command &pCommand)
{
    mCommands.remove(pCommand.getName());
}

void UI::CommandParser::parseString(const QString& pCommand_str)
{
    //should be owerwrite with stringview, unnececary init new stings
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
            qio::qout << "[ERROR]: Unknown command!\n";
            qio::qout.flush();
        }

    }

}

const UI::CommandParser::command_map &UI::CommandParser::getCommands() const
{
    return mCommands;
}

UI::CommandParser::command_map UI::CommandParser::getActiveCommands() const
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
