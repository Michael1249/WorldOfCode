#ifndef UICOMPONENTMANAGER_H
#define UICOMPONENTMANAGER_H

#include <QString>
#include "Command.h"
#include "UIConstants.h"
#include "qiostream.h"

namespace UI
{

template<class Pack_t>
class UIComponent
{
public:

    UIComponent(const QString& pName,
                       const QString& pHelp_tip = "",
                       bool pTrack = true);
    ~UIComponent();

private:

    void initComponent();
    void exitComponent();

    Command mInitComponent_cmd;
    Command mExitComponent_cmd;

    Pack_t* mComponent_ptr;
    QString mName;
    bool mFlag_Track;
};

//===============================

template<class UIC_t>
UIComponent<UIC_t>::UIComponent(const QString& pName,
                                              const QString& pHelp_tip,
                                              bool pTrack):
    mInitComponent_cmd(pName + '.' + INIT_CMD_NAME,
                       getCommandDelegate(this, &UIComponent::initComponent),
                       false),
    mExitComponent_cmd(pName + '.' + EXIT_CMD_NAME,
                       getCommandDelegate(this, &UIComponent::exitComponent),
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
UIComponent<UIC_t>::~UIComponent()
{

    if(mFlag_Track)
    {
        qio::qout << UIC_EXIT_MSG << mName << endl;
    }

}

template<class UIC_t>
void UIComponent<UIC_t>::initComponent()
{
    if(!mComponent_ptr)
    {
        mComponent_ptr = new UIC_t();
    }

    mInitComponent_cmd.disable(INIT_CMD_DISABLE_REASON);
    mExitComponent_cmd.enable();

}

template<class UIC_t>
void UIComponent<UIC_t>::exitComponent()
{
    if(mComponent_ptr)
    {
        delete mComponent_ptr;
        mComponent_ptr = nullptr;
    }

    mInitComponent_cmd.enable();
    mExitComponent_cmd.disable(EXIT_CMD_DISABLE_REASON);
}

} // UI

#endif // UICOMPONENTMANAGER_H
