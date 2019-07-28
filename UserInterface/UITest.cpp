#include "qiostream.h"
#include "UITest.h"

UIC_Test::UIC_Test():
    mFoo_cmd("test.foo", UI::getCommandDelegate(this, &UIC_Test::foo))
{
    mFoo_cmd.addHelpTip("test Command")
            .addArg(
                UI::ArgInfo
                {
                    .name = "str",
                    .short_name = 's',
                    .help_tip = "some help"
                }
            );
}

void UIC_Test::foo(const QString &str)
{
    qio::qout << __FUNCTION__ << " : " << str <<endl;
}
