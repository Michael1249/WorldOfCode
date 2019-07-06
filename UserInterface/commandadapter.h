#ifndef COMMANDADAPTER_H
#define COMMANDADAPTER_H

#include <QStringList>
#include "delegate.h"

namespace UserInterface
{

class ICommandAdapter
{
public:
    virtual ~ICommandAdapter() = default;

    virtual void call(QStringList pArg_value_list) = 0;

};

template <typename T, typename R, typename ...Args>
class CommandAdapter: public ICommandAdapter
{
public:
   void call(QStringList pArg_value_list) = 0;
private:
    Support::Delegate<T, R, Args...>* delegate;
};



} // UserInterface

#endif // COMMANDADAPTER_H
