#ifndef USERCOMMAND_H
#define USERCOMMAND_H

#include "command.h"
#include "interface.h"

namespace UserInterface
{

class UserCommand: public Command
{
public:
    UserCommand(const QString& pName,
                const QString& pHelp,
                const QVector<ArgumentInfo>& pArgs_info,
                Delegate_ptr_t pAdapter);
    ~UserCommand();
};

} //UserInterface

#endif // USERCOMMAND_H
