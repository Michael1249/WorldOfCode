#include <QCoreApplication>
#include "UserInterface/interface.h"
#include "UserInterface/usercomponentmanager.h"
#include "qiostream.h"

class TestComponent
{
    void foo(const QString& pStr)
    {
        QIO::qout << __FUNCTION__ << " : " << pStr << endl;
    }

    UI::User::UserCommand cmd_foo =
    {
        UI::getCommandDelegate(*this, &TestComponent::foo),
        "test.foo",
        {
            {"str", 's'}
        },
        "test string out"
    };

    static UI::User::UserComponentManager<TestComponent> manager;
};

UI::User::UserComponentManager<TestComponent> TestComponent::manager("test");

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI::User::Run();

    return a.exec();
}
