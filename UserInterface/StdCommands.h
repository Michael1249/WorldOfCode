#ifndef STDCOMMANDS_H
#define STDCOMMANDS_H

#include "QString"
#include "Command.h"

namespace UI
{

class StdCommands
{
public:

    StdCommands() = default;

private:

    void help_request(const QString& pStr);
    Command cmd_help_request = std::move(
            Command("help", false)
            .linkTo( this, &StdCommands::help_request)
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

} // UI

#endif // STDCOMMANDS_H
