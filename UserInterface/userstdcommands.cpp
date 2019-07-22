#include "interface.h"
#include "qiostream.h"
#include "userstdcommands.h"

void UI::API::UserStdCommands::help_request(const QString &pStr)
{
    QStringList result_output;
    auto commands = UI::API::Interface::getInstance()->getParser().getCommands();
    int max_length = 0;

    for(auto command : commands)
    {
        int curr_length = command->getName().size();

        if(max_length < curr_length)
        {
            max_length = curr_length;
        }

    }

    for(auto command : commands)
    {
        auto& name = command->getName();
        if(name.contains(pStr, Qt::CaseInsensitive))
        {
            if(command->getHelpTip().size())
            {
                result_output << name + QString(max_length - name.size(), ' ') + " : " + command->getHelpTip();
            }
            else
            {
                result_output << command->getName();
            }
        }
    }
    result_output.sort();
    for(auto& str : result_output)
    {
        QIO::qout << str << '\n';
    }
    QIO::qout.flush();

}
