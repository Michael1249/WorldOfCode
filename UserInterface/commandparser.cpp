#include "commandparser.h"

void UserInterface::CommandParser::add_command(const Command &pCommand)
{
    mCommands.insert(pCommand.getName(), pCommand);
}

void UserInterface::CommandParser::parse_string(const QString& pCommand_str)
{
    //should be owerwrite with stringview, unnececary init new stings
    QString command_name = pCommand_str.section(" ", 0, 0);
    QString command_args = pCommand_str.section(" ", 1);

    if (command_name != "")
    {
        auto command_iter = mCommands.find(command_name);

        if (command_iter != mCommands.end())
        {
            command_iter.value().exec(command_args);
        }

    }

}
