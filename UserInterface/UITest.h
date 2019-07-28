#ifndef UITEST_H
#define UITEST_H

#include "UIComponent.h"

class UITest
{
public:
    UITest();

private:
    void foo(const QString& str);
    UI::Command mFoo_cmd;

};

#endif // UITEST_H
