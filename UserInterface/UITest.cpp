#include "qiostream.h"
#include "UITest.h"

UITest::UITest()
{
    UI::CommandInfo info;
    info.setName("test.foo");
    info.setHelpTip("test Command");
    info.addArg(
                UI::ArgInfo
                {
                    .name = "str",
                    .short_name = 's',
                   // .help_tip = "some help"
                }
            );
    mFoo_cmd.addToUI(info);
}

void UITest::foo(const QString &str)
{
    qio::qout << __FUNCTION__ << " : " << str <<endl;
}
