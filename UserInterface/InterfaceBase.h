#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H

#include "Command.h"

namespace UI
{

class InterfaceBase
{
public:
    virtual void addCommand_slot(Command& pCommand, const CommandInfo& pInfo) = 0;
    virtual void removeCommand_slot(const QString &pCommand_name) = 0;
    virtual ~InterfaceBase() = default;
};

} // UI

#endif // INTERFACEBASE_H
