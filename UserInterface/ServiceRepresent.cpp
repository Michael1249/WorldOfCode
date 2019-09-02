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
    qio::qout << CMD_INIT_MSG << pInfo.getName() << endl;
    auto command_rep = mCommands.insert(
                pInfo.getName(),
                QPointer<CommandRepresent>(new CommandRepresent(pInfo))
    ).value().data();
    QObject::connect(command_rep, SIGNAL(destroyed(const QString&)), this, SLOT(removeCommand_slot(const QString&)));

    return command_rep;
}

void ServiceRepresent::removeCommand_slot(const QString &pCommand_name)
{
    qio::qout << CMD_EXIT_MSG << pCommand_name << endl;
    mCommands.remove(pCommand_name);
}

void ServiceRepresent::processCommand(const QString& pCommand_str)
{

    //TODO: owerwrite with stringview, unnececary init new stings
    QString command_name = pCommand_str.section(" ", 0, 0);
    QString command_args = pCommand_str.section(" ", 1);

    if (command_name != "")
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
