#include "interface.h"
#include "qiostream.h"
#include "userstdcommands.h"

void UI::User::UserStdCommands::help_request(const QString &pStr)
{
      auto command_map = UI::User::Interface::getInstance()->getParser().getCommands();

      command_map.erase(std::remove_if(command_map.begin(), command_map.end(),
                     [pStr](auto command)
                     {
                        return !command->getName().contains(pStr, Qt::CaseInsensitive);
                     }));

      if (command_map.size() == 0)
      {
          QIO::qout << "Nothing found" << endl;
      }
      else if(command_map.size() == 1)
      {
          auto command = command_map.begin().value();
          QIO::qout << command->getName();

          for (auto& arg: command->getArgumentsInfo())
          {
              QIO::qout << QString(" <%1>").arg(arg.arg_name);
          }

          QIO::qout << endl;

          if(command->hasHelpTip())
          {
              QIO::qout << command->getHelpTip() << endl;
          }

          QIO::qout << left;

          for (auto& arg: command->getArgumentsInfo())
          {
              QIO::qout << QString("<%1, %2> = \"%3\"")
                           .arg(arg.arg_name)
                           .arg(arg.arg_short_name)
                           .arg(arg.default_value)
                        << endl
                        << arg.help_tip
                        << endl;
          }

      }
      else
      {
          for(auto command : command_map)
          {
              QIO::qout << qSetFieldWidth(12)
                        << left
                        << command->getName();
              if(command->hasHelpTip())
              {
                  QIO::qout << qSetFieldWidth(0)
                            << " : "
                            << command->getHelpTip();
              }
              QIO::qout << endl;
          }
      }

    QIO::qout.flush();
}
