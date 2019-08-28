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

    template<class obj_t, class mFunc_t>
    void addCommand(obj_t& pObj, mFunc_t pFunc, const CommandInfo& pInfo);

    virtual ~InterfaceBase() = default;
};

template<class obj_t, class mFunc_t>
void InterfaceBase::addCommand(obj_t& pObj, mFunc_t pFunc, const CommandInfo& pInfo)
{
    Command* cmd = new Command(&pObj);
    cmd->link_to(&pObj, pFunc);
    addCommand_slot(*cmd, pInfo);
}

} // UI

#endif // INTERFACEBASE_H
