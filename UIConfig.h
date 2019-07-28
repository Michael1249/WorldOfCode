#ifndef UICONFIG_H
#define UICONFIG_H

#include "UserInterface/Interface.h"
#include "UserInterface/UITest.h"
#include "Server/UIC_Server/UIC_Server.h"

void setUpUI()
{
    UI::addStaticUIComponent<UIC_Test>("test", "Test UI");
    UI::addStaticUIComponent<UIC_Server>("server");
}


#endif // UICONFIG_H
