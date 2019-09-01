#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H

#include "Command.h"
#include "UIConstants.h"

namespace UI
{
class ServiceBase;
class InterfaceBase
{
public:

    Q_DISABLE_COPY_MOVE(InterfaceBase)
    InterfaceBase() = default;
    virtual ~InterfaceBase() = default;

    template<class obj_t, class mFunc_t>
    void addGlobalCommand(obj_t* pObj, mFunc_t pFunc, const CommandInfo& pInfo);

protected:
    friend class ServiceBase;

    template<class obj_t, class mFunc_t>
    void addCommand(const QString& pService_name, obj_t* pObj, mFunc_t pFunc, const CommandInfo& pInfo);
    virtual void addService(ServiceBase* pServise) = 0;
    virtual void addExistCommand(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo) = 0;
    virtual void addService_slot(const QString& pName, const QString& pHelp_tip) = 0;
    virtual void removeService_slot(const QString& pName) = 0;

};

template<class obj_t, class mFunc_t>
void InterfaceBase::addGlobalCommand(obj_t *pObj, mFunc_t pFunc, const CommandInfo &pInfo)
{
    addCommand(GLOBAL_SERVICE_NAME, pObj, pFunc, pInfo);
}

template<class obj_t, class mFunc_t>
void InterfaceBase::addCommand(const QString& pService_name, obj_t* pObj, mFunc_t pFunc, const CommandInfo& pInfo)
{
    Command* cmd = new Command(pObj, pInfo);
    cmd->link_to(pObj, pFunc);
    addExistCommand(pService_name, *cmd, pInfo);
}

} // UI

#endif // INTERFACEBASE_H
