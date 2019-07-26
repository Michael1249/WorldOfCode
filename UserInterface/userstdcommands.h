#ifndef USERSTDCOMMANDS_H
#define USERSTDCOMMANDS_H

#include "QString"
#include "interface.h"
#include "commandadapter.h"
#include "command.h"

namespace UI
{
namespace User
{

class UserStdCommands
{
public:
    UserStdCommands() = default;

    void help_request(const QString& pStr);
    Command cmd_help_request = std::move(
            Command("help", false)
            .setAdapter( this, &UserStdCommands::help_request)
            .addArg(
                ArgInfo
                {
                    .name="filter",
                    .short_name = 'f',
                    .help_tip = "search for commands which contain <filter>,\n"
                                "show command's details if it's found."
                }
             )
             .addHelpTip("helps to find command and get discription")
        );

};

} // API
} // UI

#endif // USERSTDCOMMANDS_H
