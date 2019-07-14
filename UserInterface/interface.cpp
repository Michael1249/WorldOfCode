#include <QTextStream>
#include "qiostream.h"
#include "interface.h"

UserInterface::Interface* UserInterface::Interface::p_instance = nullptr;

UserInterface::Interface::Interface()
{
}

void UserInterface::Interface::addCommand(const UserInterface::Command &pCommand)
{
    mParser.addCommand(pCommand);
}

void UserInterface::Interface::removeCommand(const UserInterface::Command &pCommand)
{
    mParser.removeCommand(pCommand);
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

        mParser.parseString(args_str);
    }

}

