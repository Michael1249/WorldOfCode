#include "qiostream.h"
#include "UITest.h"

UITest::UITest()
{
    mFoo_cmd.setName("test.foo")
            .link_to(this, &UITest::foo)
            .setHelpTip("test Command")
            .addArg(
                UI::ArgInfo
                {
                    .name = "str",
                    .short_name = 's',
                    .help_tip = "some help"
                }
            ).addToUI();
}

void UITest::foo(const QString &str)
{
    qio::qout << __FUNCTION__ << " : " << str <<endl;
}
