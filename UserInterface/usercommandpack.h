#ifndef USERCOMMANDPACK_H
#define USERCOMMANDPACK_H

#include <QList>
#include <memory>
#include "usercommand.h"

namespace UserInterface
{

class UserCommandPack
{
public:
    UserCommandPack();

private:
    QList<const std::unique_ptr<UserInterface::UserCommand>> mUser_command_list;
};

} // UserInterface

#endif // USERCOMMANDPACK_H
