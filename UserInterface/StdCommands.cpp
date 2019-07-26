#include "Interface.h"
#include "qiostream.h"
#include "StdCommands.h"

void UI::StdCommands::help_request(const QString &pStr)
{
      auto command_map = UI::Interface::getInstance().getParser().getCommands();

      for(auto iter = command_map.begin(); iter != command_map.end();)
      {
          if(!iter.value()->getName().contains(pStr, Qt::CaseInsensitive))
          {
               iter = command_map.erase(iter);
          }
          else
          {
            ++iter;
          }
      }

      if (command_map.size() == 0)
      {
          qio::qout << "Nothing found" << endl;
      }
      else if(command_map.size() == 1)
      {
          auto command = command_map.begin().value();
          qio::qout << command->getName();

          for (auto& arg: command->getArgumentsInfo())
          {
              qio::qout << QString(" <%1>").arg(arg.name);
          }

          qio::qout << endl;

          if(command->hasHelpTip())
          {
              qio::qout << command->getHelpTip() << endl;
          }

          if(command->getArgumentsInfo().size())
          {
              qio::qout << left;

              for (auto& arg: command->getArgumentsInfo())
              {
                  qio::qout << QString(40, '_')
                            << endl
                            << QString("<%1, %2> = \"%3\"")
                               .arg(arg.name)
                               .arg(arg.short_name)
                               .arg(arg.default_value)
                            << endl
                            << arg.help_tip
                            << endl;
              }

          }
          else
          {
              qio::qout << "Without arguments." << endl;
          }

      }
      else
      {
          for(auto command : command_map)
          {
              qio::qout << qSetFieldWidth(16)
                        << left
                        << command->getName();
              if(command->hasHelpTip())
              {
                  qio::qout << qSetFieldWidth(0)
                            << " : "
                            << command->getHelpTip();
              }
              qio::qout << endl;
          }
      }

    qio::qout.flush();
}
