#ifndef UITEST_H
#define UITEST_H

#include "UIComponentManager.h"

class UIC_Test
{
public:
    UIC_Test();

private:
    void foo(const QString& str);
    UI::Command mFoo_cmd;

};

#endif // UITEST_H
