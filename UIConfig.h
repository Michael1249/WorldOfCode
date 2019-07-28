#ifndef UICONFIG_H
#define UICONFIG_H

#include "UserInterface/Interface.h"
#include "UserInterface/UITest.h"
#include "Server/ServerUIComponent/ServerUIComponent.h"

void setUpUI()
{
    UI::addStaticUIComponent<UITest>("test", "Test UI");
    UI::addStaticUIComponent<ServerUIComponent>("server");
}


#endif // UICONFIG_H
