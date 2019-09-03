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
    Command& addCommand(obj_t* pObj, mFunc_t pFunc, const CommandInfo& pInfo, QString* pServiceName = nullptr);
    void addService(ServiceBase* pServise);
    virtual void connectSyncSignal(ServiceBase* pServise) = 0;
    virtual void connectSyncSignal(Command* pCommand) = 0;
    virtual void addExistCommand(Command* pCommand) = 0;
    virtual void addService_slot(const QString& pName, const QString& pHelp_tip) = 0;
    virtual void removeService_slot(const QString& pName) = 0;

};

template<class obj_t, class mFunc_t>
void InterfaceBase::addGlobalCommand(obj_t *pObj, mFunc_t pFunc, const CommandInfo &pInfo)
{
    addCommand(pObj, pFunc, pInfo);
}

template<class obj_t, class mFunc_t>
Command& InterfaceBase::addCommand(obj_t* pObj, mFunc_t pFunc, const CommandInfo& pInfo, QString* pServiceName)
{
    Command* cmd = new Command(pObj, pInfo);
    cmd->link_to(pObj, pFunc);
    cmd->setServiceName(pServiceName);
    addExistCommand(cmd);
    connectSyncSignal(cmd);
    return *cmd;
}

} // UI

#endif // INTERFACEBASE_H
