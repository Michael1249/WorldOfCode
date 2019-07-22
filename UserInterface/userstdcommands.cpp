#include <algorithm>
#include "interface.h"
#include "qiostream.h"
#include "userstdcommands.h"

void UI::API::UserStdCommands::help_request(const QString &pStr)
{
      auto command_map = UI::API::Interface::getInstance()->getParser().getCommands();

      command_map.erase(std::remove_if(command_map.begin(), command_map.end(),
                     [pStr](auto command)
                     {
                        return !command->getName().contains(pStr, Qt::CaseInsensitive);
                     }));

      if (command_map.size() == 0)
      {

      }
      else if(command_map.size() == 1)
      {
          auto command = command_map.begin().value();
          QIO::qout << command->getName();
          if(command->hasHelpTip())
          {
              QIO::qout << qSetFieldWidth(20) << ": " << command->getHelpTip() << qSetFieldWidth(0);
          }
          QIO::qout << '\n';
          for (auto& arg : command->getArgumentsInfo())
          {
              QIO::qout << QString("[%1, %2] = \"%3\"").arg(arg.arg_name).arg(arg.arg_short_name).arg(arg.default_value)
                        << qSetFieldWidth(20)
                        << ": "
                        << arg.help_tip
                        << qSetFieldWidth(0)
                        << '\n';
          }
      }
      else
      {
          for(auto command : command_map)
          {
              QIO::qout << command->getName();
              if(command->hasHelpTip())
              {
                  QIO::qout << qSetFieldWidth(16) << ": " << command->getHelpTip() << qSetFieldWidth(0);
              }
              QIO::qout << '\n';
          }
      }

    QIO::qout.flush();
}
