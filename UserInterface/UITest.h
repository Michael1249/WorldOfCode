#ifndef UICONSTANTS_H
#define UICONSTANTS_H

#include "qiostream.h"
#include "UIComponentManager.h"

UI_STATIC_COMPONENT(UIC_Test, "test", "test UIC manager")
class UIC_Test
{
    void foo(const QString& str)
    {
        qio::qout << __FUNCTION__ << " : " << str <<endl;
    }

    UI::Command cmd_help_request = std::move(
            UI::Command("foo")
            .linkTo( this, &UIC_Test::foo)
            .addArg(
                UI::ArgInfo
                {
                    .name="str",
                    .short_name = 's',
                    .help_tip = "arg help tip"
                }
             )
             .addHelpTip("command help tip")
        );

};

#endif // UICONSTANTS_H
