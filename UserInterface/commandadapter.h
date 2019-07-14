#ifndef COMMANDADAPTER_H
#define COMMANDADAPTER_H

#include <QStringList>
#include <memory>
#include "delegate.h"
namespace UserInterface
{

class ICommandDelegate
{
public:
    virtual void Invoke(const QStringList&) = 0;
    virtual ~ICommandDelegate() = default;
};

template<class obj_t, class ret_val_t, class ...mem_func_args_t>
class CommandDelegate: public Support::MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>,
                       public ICommandDelegate
{
public:
    CommandDelegate(obj_t& obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...)):
        Support::MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>(obj, mem_func_ptr)
    {

    }

    void Invoke(const QStringList& args) override
    {
        Support::MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>::Invoke(args);
    }

};

template<class obj_t, class ret_val_t, class ...mem_func_args_t>
auto getCommandDelegate(obj_t& obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...))
{
    return std::unique_ptr<CommandDelegate<obj_t, ret_val_t, mem_func_args_t...>>
           (new CommandDelegate<obj_t, ret_val_t, mem_func_args_t...>(obj, mem_func_ptr));
}

} // UserInterface

#endif // COMMANDADAPTER_H
