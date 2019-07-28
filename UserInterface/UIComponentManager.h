#ifndef UICOMPONENTMANAGER_H
#define UICOMPONENTMANAGER_H

#include <QString>
#include "Command.h"
#include "UIConstants.h"
#include "qiostream.h"

namespace UI
{

/*
singleton wrapper for UIC_t.

Where UIC_t is any custom class, which has default constructor
and contain feilds with type "Command".

Naming convention: All UIComponent's type names will be started with 'UIC_'

Manager define 'init' and 'exit' commands for UIC
*/
template<class UIC_t>
class UIComponentManager
{
public:

    UIComponentManager(const QString& pName,
                       const QString& pHelp_tip = "",
                       bool pTrack = true);
    ~UIComponentManager();

private:

    void initComponent();
    void exitComponent();

    Command mInitComponent_cmd;
    Command mExitComponent_cmd;

    static UIC_t* p_component;
    QString mName;
    bool mFlag_Track;
};

//===============================

template <class UIC_t>
UIC_t* UIComponentManager<UIC_t>::p_component = nullptr;

template<class UIC_t>
UIComponentManager<UIC_t>::UIComponentManager(const QString& pName,
                                              const QString& pHelp_tip,
                                              bool pTrack):
    mInitComponent_cmd(pName + '.' + INIT_CMD_NAME,
                       getCommandDelegate(this, &UIComponentManager::initComponent),
                       false),
    mExitComponent_cmd(pName + '.' + EXIT_CMD_NAME,
                       getCommandDelegate(this, &UIComponentManager::exitComponent),
                       false),
    mName(pName),
    mFlag_Track(pTrack)
{

    mInitComponent_cmd.addHelpTip(INIT_CMD_HELP_TIP.arg(pName).arg(pHelp_tip));
    mExitComponent_cmd.addHelpTip(EXIT_CMD_HELP_TIP.arg(pName).arg(pHelp_tip));
    mExitComponent_cmd.disable();

    if(mFlag_Track)
    {
        qio::qout << UIC_INIT_MSG << mName << endl;
    }

}

template<class UIC_t>
UIComponentManager<UIC_t>::~UIComponentManager()
{

    if(mFlag_Track)
    {
        qio::qout << UIC_EXIT_MSG << mName << endl;
    }

}

template<class UIC_t>
void UIComponentManager<UIC_t>::initComponent()
{
    if(!p_component)
    {
        p_component = new UIC_t();
    }

    mInitComponent_cmd.disable(INIT_CMD_DISABLE_REASON);
    mExitComponent_cmd.enable();

}

template<class UIC_t>
void UIComponentManager<UIC_t>::exitComponent()
{
    if(p_component)
    {
        delete p_component;
        p_component = nullptr;
    }

    mInitComponent_cmd.enable();
    mExitComponent_cmd.disable(EXIT_CMD_DISABLE_REASON);
}

} // UI

#endif // UICOMPONENTMANAGER_H
