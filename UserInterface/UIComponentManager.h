#ifndef UICOMPONENTMANAGER_H
#define UICOMPONENTMANAGER_H

#include <QString>
#include "Command.h"

//TODO: overwrite without macro
// Add static ui component to Interface
#define UI_STATIC_COMPONENT(type, name, help_tip)\
    class type;\
    namespace UIComponents\
    {\
        static UI::UIComponentManager<type> type ( name , help_tip );\
    }\

namespace UI
{

/*
singleton wrapper for UIComponent_T.

Where UIComponent_T is any custom class, which has default constructor
and contain feilds with type "Command".

Naming convention: All UIComponent's type names will be started with 'UIC_'

It provides global access to unique UIComponent object,
and define 'init' and 'exit' commands for it
*/
template<class UIComponent_T>
class UIComponentManager
{
public:

    UIComponentManager(const QString& component_name, const QString& help_tip = "");

    //return pointer to UIComponent if exist, else nullptr
    static UIComponent_T* getComponent();

private:

    UIComponent_T* initComponent();

    void deleteComponent();

    Command mInit_command;
    Command mExit_command;

    static UIComponent_T* p_component;
};

template <class UIComponent_T>
UIComponent_T* UIComponentManager<UIComponent_T>::p_component = nullptr;

template <class UIComponent_T>
auto setUIComponentManager(const QString& component_name, const QString& help_tip = "")
{
    static UIComponentManager<UIComponent_T> manager(component_name, help_tip);
    return &manager;
}

template<class UIComponent_T>
UIComponentManager<UIComponent_T>::UIComponentManager(const QString& component_name, const QString& help_tip):
    mInit_command(component_name + ".init", false),
    mExit_command(component_name + ".exit", false)
{
    mInit_command
            .linkTo(getCommandDelegate(this, &UIComponentManager::initComponent))
            .addHelpTip("init component - " + component_name + ". " + help_tip);

    mExit_command
            .linkTo(getCommandDelegate(this, &UIComponentManager::deleteComponent))
            .addHelpTip("exit component - " + component_name + ". " + help_tip)
            .disable();
}

template<class UIComponent_T>
UIComponent_T* UIComponentManager<UIComponent_T>::getComponent()
{
    return p_component;
}

template<class UIComponent_T>
UIComponent_T* UIComponentManager<UIComponent_T>::initComponent()
{
    if(!p_component)
    {
        p_component = new UIComponent_T();
    }

    mInit_command.disable("Component already init");
    mExit_command.enable();

    return p_component;
}

template<class UIComponent_T>
void UIComponentManager<UIComponent_T>::deleteComponent()
{
    if(p_component)
    {
        delete p_component;
        p_component = nullptr;
    }

    mInit_command.enable();
    mExit_command.disable("Component already exit");
}

} // UI

#endif // UICOMPONENTMANAGER_H
