#ifndef SERVICEBASE_H
#define SERVICEBASE_H

#include "InterfaceBase.h"

namespace UI
{

class ServiceBase : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ServiceBase)

public:
    ServiceBase(InterfaceBase* pInterface, const QString& pName, const QString& pHelp_tip = "");
    ~ServiceBase();

    const QString& getName();
    const QString& getHelpTip();

signals:
    void destroyCommands_signal();

protected:
    template<class obj_t, class mFunc_t>
    void addCommand(obj_t* pObj, mFunc_t pFunc, const CommandInfo& pInfo);
    InterfaceBase* getInterface();

private:
    void connectDestroyCommands_signal(Command* cmd);

    QString mName;
    QString mHelp_tip;
    InterfaceBase* mInterface;
};

template<class obj_t, class mFunc_t>
void ServiceBase::addCommand(obj_t *pObj, mFunc_t pFunc, const CommandInfo &pInfo)
{
    Command& cmd = mInterface->addCommand(pObj, pFunc, pInfo, this);
    connectDestroyCommands_signal(&cmd);
}


} // UI

#endif // SERVICEBASE_H
