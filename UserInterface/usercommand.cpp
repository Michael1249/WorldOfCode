#include "usercommand.h"

UserInterface::UserCommand::UserCommand(const QString &pName,
                                        const QString &pHelp,
                                        const QVector<UserInterface::Command::ArgumentInfo> &pArgs_info,
                                        UserInterface::Command::Delegate_ptr_t pAdapter):
    Command (pName, pHelp, pArgs_info, std::move(pAdapter))
{
    UserInterface::Interface::getInstance()->addCommand(*this);
}

UserInterface::UserCommand::~UserCommand()
{
    UserInterface::Interface::getInstance()->removeCommand(*this);
}
