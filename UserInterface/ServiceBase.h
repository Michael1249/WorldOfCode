#ifndef SERVICEBASE_H
#define SERVICEBASE_H

#include "InterfaceBase.h"

namespace UI
{

class ServiceBase : public QObject
{
public:
    ServiceBase(InterfaceBase* pInterface, const QString& pName, const QString& pHelp_tip = "");
    ~ServiceBase();

    const QString& getName();

protected:
    template<class obj_t, class mFunc_t>
    void addCommand(obj_t& pObj, mFunc_t pFunc, const CommandInfo& pInfo);

private:
    QString mName;
    InterfaceBase* mInterface;
};

template<class obj_t, class mFunc_t>
void ServiceBase::addCommand(obj_t &pObj, mFunc_t pFunc, const CommandInfo &pInfo)
{
    mInterface->addCommand(mName, pObj, pFunc, pInfo);
}


} // UI

#endif // SERVICEBASE_H
