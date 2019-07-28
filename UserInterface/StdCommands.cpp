#include "Interface.h"
#include "qiostream.h"
#include "UIConstants.h"
#include "StdCommands.h"

namespace UI
{

StdCommands::StdCommands():
    help_request_cmd("help",getCommandDelegate(this, &StdCommands::help_request), false)
{
    help_request_cmd
        .addHelpTip("helps to find command and get discription")
        .addArg(
            ArgInfo
            {
                .name="filter",
                .short_name = 'f',
                .help_tip = "search for commands which contain <filter>,\n"
                            "show command's details if it's found."
            }
        );
}

void StdCommands::help_request(const QString &pStr)
{
      auto command_map = Interface::getInstance().getParser().getCommands();

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
          qio::qout << NOTHING_FOUND_MSG << endl;
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
              qio::qout << WITHOUT_ARGUMENTS_MSG << endl;
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

} // UI
