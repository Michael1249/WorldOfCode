#ifndef COMMANDDELEGATE_H
#define COMMANDDELEGATE_H

#include <memory>
#include <QStringList>
#include "FunctionAdapter.h"

namespace UI
{

class ICommandDelegate
{
public:

    virtual void Invoke(const QVector<QString>&) = 0;
    virtual ~ICommandDelegate() = default;

};

template<class obj_t, class ret_val_t, class ...mem_func_args_t>
class CommandDelegate: public MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>,
                       public ICommandDelegate
{
public:

    CommandDelegate(obj_t& obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...)):
        MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>(obj, mem_func_ptr)
    {
    }

    void Invoke(const QVector<QString>& args) override
    {
        MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>::Invoke(args);
    }

};

template<class obj_t, class ret_val_t, class ...mem_func_args_t>
auto getCommandDelegate(obj_t* obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...))
{
    return std::unique_ptr<CommandDelegate<obj_t, ret_val_t, mem_func_args_t...>>
           (new CommandDelegate<obj_t, ret_val_t, mem_func_args_t...>(*obj, mem_func_ptr));
}

} // UI

#endif // COMMANDDELEGATE_H
