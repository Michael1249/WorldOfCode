#ifndef UICONFIG_H
#define UICONFIG_H

#include "UserInterface/Interface.h"
#include "UserInterface/UITest.h"
#include "Server/Server.h"

void setUpUI()
{
    //UI::addStaticUIComponent<UITest>("test", "Test UI");
    UI::addStaticUIComponent<Server>("server");
}


#endif // UICONFIG_H
