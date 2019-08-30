#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H

#include "Command.h"

namespace UI
{

class InterfaceBase
{
public:

    virtual ~InterfaceBase() = default;

    virtual void addCommand_slot(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo) = 0;

    template<class obj_t, class mFunc_t>
    void addCommand(const QString& pService_name, obj_t& pObj, mFunc_t pFunc, const CommandInfo& pInfo);

protected:
    friend class ServiceBase;

    virtual void addService_slot(const QString& pName, const QString& pHelp_tip) = 0;
    virtual void removeService_slot(const QString& pName) = 0;

};

template<class obj_t, class mFunc_t>
void InterfaceBase::addCommand(const QString& pService_name, obj_t& pObj, mFunc_t pFunc, const CommandInfo& pInfo)
{
    Command* cmd = new Command(&pObj);
    cmd->link_to(&pObj, pFunc);
    addCommand_slot(pService_name, *cmd, pInfo);
}

} // UI

#endif // INTERFACEBASE_H
