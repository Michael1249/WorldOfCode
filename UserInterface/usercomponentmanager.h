#ifndef USERINITCOMMAND_H
#define USERINITCOMMAND_H

#include <QString>
#include "command.h"

namespace UI
{
namespace User
{

template<class T>
class UserComponentManager
{
public:
    UserComponentManager(const QString& component_name, const QString& help_tip = ""):
        mInit_command(component_name + ".init", false),
        mExit_command(component_name + ".exit", false)
    {
        mInit_command
                .setAdapter(getCommandDelegate(this, &UserComponentManager::initComponent))
                .addHelpTip("init component - " + component_name + ". " + help_tip);

        mExit_command
                .setAdapter(getCommandDelegate(this, &UserComponentManager::deleteComponent))
                .addHelpTip("exit component - " + component_name + ". " + help_tip)
                .disable();
    }

    static T* getComponent()
    {
        return p_component;
    }

private:

    T* initComponent()
    {
        if(!p_component)
        {
            p_component = new T();
        }

        mInit_command.disable("Component already init");
        mExit_command.enable();

        return p_component;
    }

    void deleteComponent()
    {
        if(p_component)
        {
            delete p_component;
            p_component = nullptr;
        }

        mInit_command.enable();
        mExit_command.disable("Component already exit");

    }

    Command mInit_command;
    Command mExit_command;
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
