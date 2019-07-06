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
Delegate<T, R, Args...> make_delegate(T& obj, R (T::*mf)(Args...))
{
    return {obj, mf};
}

} // Support
#endif // DELEGATE_H
