#ifndef DELEGATE_H
#define DELEGATE_H

namespace Support
{

template <class Class, typename ReturnType, typename ... Parameters>
class Delegate {
    public:
        typedef ReturnType (Class::*Method)(Parameters ... params);

        Delegate(Class& ref, Method m) : obj(ref), method(m) {}
        ReturnType operator()(Parameters ... params) { return (obj.*method)(params...); }
        ReturnType Invoke(Parameters ... params) { return operator()(params...); }
    private:
        Class& obj;
        Method method;
};

template <typename T, typename R, typename ...Args>
Delegate<T, R, Args...>* new_delegate(T& obj, R (T::*mf)(Args...))
{
    return new Delegate<T, R, Args...>(obj, mf);
}

/*
Fill template arguments of class T with unsigned array from 0 to N-1
Range<T, 5>::type = T<0U, 1U, 2U, 3U, 4U>
*/
template<template<unsigned ...>class T, unsigned N, unsigned ...Args>
struct Range
{
    using type = typename Range<T, N - 1, N - 1, Args...>::type;
};

//end of recurcion 'using'
template<template<unsigned ...>class T, unsigned ...Args>
struct Range<T, 0U, Args...>
{
    using type = T<Args...>;
};

/*
adapter for member function, to call it with arguments witch will be initializate with references to items in container of arguments
Note: each argument of member function must to be able to initializate by container item
*/
template<class args_container_t, class obj_t, class ret_val_t, class ...mem_func_args_t>
class MemFuncAdapter
{

    template<unsigned ...indxs>
    struct BindArgs
    {
        static ret_val_t call(obj_t& obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...), args_container_t& args)
        {
            // necessary C - style casting
            return (obj.*mem_func_ptr)(args[indxs]...);
        }
    };

public:
    using bind_args_from_container = typename Range<BindArgs, sizeof...(mem_func_args_t)>::type;
};


//delegate based on CommandAdapter
template<class obj_t, class ret_val_t, class ...mem_func_args_t>
class MemFuncAdapterDelegate
{
public:
    MemFuncAdapterDelegate(obj_t& obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...)):
        mObj_ptr(&obj),
        mMem_func_ptr(mem_func_ptr)
    {

    }

    template<class args_container_t>
    ret_val_t Invoke(args_container_t& args) const
    {
        return MemFuncAdapter<args_container_t, obj_t, ret_val_t, mem_func_args_t...>::bind_args_from_container::call(*mObj_ptr, mMem_func_ptr, args);
    }

private:
    obj_t* mObj_ptr;
    ret_val_t(obj_t::*mMem_func_ptr)(mem_func_args_t...);
};

// This allows you to omit the template arguments.
template<class obj_t, class ret_val_t, class ...mem_func_args_t>
auto getMemFuncAdapterDelegate(obj_t& obj, ret_val_t(obj_t::*mem_func_ptr)(mem_func_args_t...))
{
    return MemFuncAdapterDelegate<obj_t, ret_val_t, mem_func_args_t...>(obj, mem_func_ptr);
}

} // Support
#endif // DELEGATE_H
