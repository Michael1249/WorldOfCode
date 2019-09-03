#include "qiostream.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "ServiceRepresent.h"

namespace UI
{

ServiceRepresent::ServiceRepresent(const QString &pName, const QString &pHelp_tip):
    mName(pName),
    mHelpTip(pHelp_tip)
{
}

CommandRepresent* ServiceRepresent::addCommand(const CommandInfo& pInfo)
{
    CommandRepresent* command_rep = nullptr;
    if(!mCommands.contains(pInfo.getName()))
    {
        qio::qout << CMD_INIT_MSG << mName << ' ' << pInfo.getName() << endl;
        command_rep = mCommands.insert(
                    pInfo.getName(),
                    QPointer<CommandRepresent>(new CommandRepresent(pInfo))
        ).value().data();
        QObject::connect(command_rep, SIGNAL(commandDestroyed_signal(const QString&)), this, SLOT(removeCommand_slot(const QString&)));

    }
    else
    {
        qio::qout << "[ERROR]: Can not add command '" + pInfo.getName() + "' to service '" + mName + "'. Command allready exists." << endl;
    }

    return command_rep;
}

void ServiceRepresent::removeCommand_slot(const QString &pCommand_name)
{
    qio::qout << CMD_EXIT_MSG << mName << ' ' << pCommand_name << endl;
    mCommands.remove(pCommand_name);
}

void ServiceRepresent::processCommand(const QString& pCommand_str)
{

    //TODO: owerwrite with stringview, unnececary init new stings
    QString command_name = pCommand_str.section(" ", 0, 0);
    QString command_args = pCommand_str.section(" ", 1);

    if (!command_name.isEmpty())
    {
        auto command_iter = mCommands.find(command_name);

        if (command_iter != mCommands.end())
        {
            command_iter.value()->execCommand(command_args);
        }
        else
        {
            qio::qout << "[ERROR]:" << ERR_UNKNOWN_CMD << endl;
            qio::qout.flush();
        }

    }

}

const ServiceRepresent::CommandMap &ServiceRepresent::getCommands() const
{
    return mCommands;
}


} // UI
