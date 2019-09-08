#include "ServiceBase.h"


UI::ServiceBase::ServiceBase(UI::InterfaceBase *pInterface, const QString &pName, const QString& pHelp_tip):
    mName(pName),
    mHelp_tip(pHelp_tip),
    mInterface(pInterface)
{
    mInterface->addService(this);
}

UI::ServiceBase::~ServiceBase()
{
    mInterface->removeService_slot(mName);
    emit destroyCommands_signal();
}

const QString &UI::ServiceBase::getName()
{
    return mName;
}

const QString &UI::ServiceBase::getHelpTip()
{
    return mHelp_tip;
}

UI::InterfaceBase* UI::ServiceBase::getInterface()
{
    return mInterface;
}
void UI::ServiceBase::connectDestroyCommands_signal(UI::Command *cmd)
{
    QObject::connect(this, SIGNAL(destroyCommands_signal()), cmd, SLOT(deleteLater()));
}
