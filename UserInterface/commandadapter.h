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
    CommandAdapter(T& obj, R (T::*mf)(Args...))
    {
        mDelegate = make_delegate(obj, mf);
    }

   void call(QStringList pArg_value_list) = 0;
private:
   Support::Delegate<T, R, Args...>* mDelegate;
};




} // UserInterface

#endif // COMMANDADAPTER_H
