#ifndef USERINITCOMMAND_H
#define USERINITCOMMAND_H

#include <QString>
#include "usercommand.h"

namespace UI
{
namespace User
{

template<class T>
class UserComponentManager
{
public:
    UserComponentManager(const QString& component_name, const QString& help_tip = ""):
        mInit_commnd
        {
            getCommandDelegate(*this, &UserComponentManager::getInstance),
            component_name + ".init",
            {
                {}
            },
            "Initial component - " + component_name + ". " + help_tip,
            false
        },
        mExit_commnd
        {
            getCommandDelegate(*this, &UserComponentManager::deleteComponent),
            component_name + ".exit",
            {
                {}
            },
            "Exit component - " + component_name + ". " + help_tip,
            false
        }
    {
        mExit_commnd.setEnable(false);
    }

private:

    T* getInstance()
    {
        if(!p_component)
        {
            p_component = new T();
        }

        return p_component;
    }

    void deleteComponent()
    {
        if(p_component)
        {
            delete p_component;
        }

    }

    UserCommand mInit_commnd;
    UserCommand mExit_commnd;
    static T* p_component;
};

template <class T>
T* UserComponentManager<T>::p_component = nullptr;

template <class T>
auto setComponentManager(const QString& component_name, const QString& help_tip = "")
{
    static UserComponentManager<T> manager(component_name, help_tip);
    return &manager;
}

} // API
} // UI

#endif // USERINITCOMMAND_H
