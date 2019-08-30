#include "ServiceBase.h"


UI::ServiceBase::ServiceBase(UI::InterfaceBase *pInterface, const QString &pName, const QString& pHelp_tip):
    mName(pName),
    mInterface(pInterface)
{
    pInterface->addService_slot(pName, pHelp_tip);
}

UI::ServiceBase::~ServiceBase()
{
    mInterface->removeService_slot(mName);
}

const QString &UI::ServiceBase::getName()
{
    return mName;
}
