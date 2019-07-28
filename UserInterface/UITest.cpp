#include "qiostream.h"
#include "UITest.h"

UITest::UITest():
    mFoo_cmd("test.foo", UI::getCommandDelegate(this, &UITest::foo))
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

void UITest::foo(const QString &str)
{
    qio::qout << __FUNCTION__ << " : " << str <<endl;
}
