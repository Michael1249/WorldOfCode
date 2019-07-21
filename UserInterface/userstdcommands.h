#ifndef USERSTDCOMMANDS_H
#define USERSTDCOMMANDS_H

#include "QString"
#include "interface.h"
#include "commandadapter.h"
#include "usercommand.h"

namespace UI
{
namespace API
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
            {"cmd", 'c'}
        },
        ""
    };
};

} // API
} // UI

#endif // USERSTDCOMMANDS_H
