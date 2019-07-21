#include "qiostream.h"
#include "commandparser.h"

void UI::CommandParser::addCommand(const Command &pCommand)
{
    mCommands.insert(pCommand.getName(), &pCommand);
}

void UI::CommandParser::removeCommand(const UI::Command &pCommand)
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
            QIO::qout << "[ERROR]: Unknown command!\n";
            QIO::qout.flush();
        }

    }

}
