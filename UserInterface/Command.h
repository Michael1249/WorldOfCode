#ifndef COMMAND_H
#define COMMAND_H

#include <type_traits>
#include <memory>
#include <QVector>
#include "CommandDelegate.h"
#include "CommandRepresent_source.h"
#include "CommandInfo.h"

namespace UI
{
class ServiceBase;
/*
Represetn interface between User (Input) and c++ function

Provide to call function with user's input string line

Note: each argument of function must to be able to initializate by QString object
*/
class Command: public QObject
{
    Q_OBJECT

public:

    Q_DISABLE_COPY_MOVE(Command)
    Command(QObject* parent, CommandInfo pInfo, ServiceBase* pService = nullptr);
    ~Command();

    const CommandInfo& getInfo() const;
    const QString& getServiceName() const;
    const ServiceBase* getService() const;

    template<class Obj_t, class MFunc_t>
    void link_to(Obj_t* pObj_ptr, MFunc_t pMfunc_ptr);

public slots:
    virtual void exec_slot(const QVector<QString> & pArg_vals);

signals:
    void destroyed_signal();

private:
    CommandInfo mInfo;
    ServiceBase* mService = nullptr;
    std::unique_ptr<ICommandDelegate> mDelegate;
};

template<class Obj_t, class MFunc_t>
void Command::link_to(Obj_t *pObj_ptr, MFunc_t pMfunc_ptr)
{
    mDelegate = getCommandDelegate(pObj_ptr, pMfunc_ptr);
}

} //UI

#endif // COMMAND_H
