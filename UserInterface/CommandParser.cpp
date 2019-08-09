#include "qiostream.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "CommandParser.h"

namespace UI
{

void CommandParser::addCommand(const Command &pCommand, const CommandInfo& pInfo)
{

    if (mCommands.find(pInfo.getName()) != mCommands.end())
    {
        throw QExceptionMessage(ERR_CMD_REDEFINE.arg(pInfo.getName()));
    }

    auto command_rep = mCommands.insert(
                pInfo.getName(),
                QPointer<CommandRepresent>(new CommandRepresent(pInfo))
    ).value().data();

    QObject::connect(command_rep, SIGNAL(exec(const QVector<QString>&)), &pCommand, SLOT(exec_slot(const QVector<QString>&)));
}

void CommandParser::removeCommand(const QString &pCommand_name)
{
    mCommands.remove(pCommand_name);
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
            command_iter.value()->callCommand(pCommand_str);
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
