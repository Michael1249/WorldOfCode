#include <QTextStream>
#include "qiostream.h"
#include "interface.h"

class Target
{
public:
    void foo(QString s)
    {
        QIO::qout << "This is Target::foo\n"
                  << "Your argument: "
                  << s
                  << '\n';
        QIO::qout.flush();
    }
};

Target target;

UserInterface::Interface* UserInterface::Interface::p_instance = nullptr;

UserInterface::Interface::Interface()
{
}

UserInterface::Interface *UserInterface::Interface::getInstance()
{
    if (nullptr == p_instance)
    {
        p_instance = new Interface();
    }
    return p_instance;
}

void UserInterface::Interface::run()
{
    using namespace QIO;
    while (!flag_run_end)
    {
        qout << ">>>";
        qout.flush();

        QString args_str = qin.readLine();

        mParser.parse_string(args_str);
    }

}

