#ifndef USERSTDCOMMANDS_H
#define USERSTDCOMMANDS_H

#include "QString"
#include "interface.h"
#include "commandadapter.h"
#include "usercommand.h"

namespace UI
{
namespace User
{

class UserStdCommands
{
public:
    UserStdCommands() = default;

    void help_request(const QString& pStr);
    UserCommand cmd_help_request =
    {
        getCommandDelegate(*this, &UserStdCommands::help_request),
        "help",
        {
            {
                "filter",
                'f',
                "search for commands which contain <filter>,\n"
                "show command's details if it's found."
            }
        },
        "helps to find command and get discription",
        false
    };
};

} // API
} // UI

#endif // USERSTDCOMMANDS_H
