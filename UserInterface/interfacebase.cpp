#include "InterfaceBase.h"
#include "ServiceBase.h"

void UI::InterfaceBase::addService(UI::ServiceBase *pServise)
{
    addService_slot(pServise->getName(), pServise->getHelpTip());
    connectSyncSignal(pServise);
}
