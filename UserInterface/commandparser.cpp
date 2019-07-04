#include <sstream>
#include <vector>
#include "commandparser.h"

void CommandParser::add_command(const Command &pCommand)
{
    mCommands.insert({pCommand.getName(), pCommand});
}

const std::string& CommandParser::parse_string(const std::string& pCommand_str)
{
    std::string const* responce = &RESP_EMPTY_STRING;
    std::istringstream parse(pCommand_str);

    std::string command_name;
    parse >> command_name;

    if (command_name != "")
    {
        auto command_iter = mCommands.find(command_name);

        if (command_iter != mCommands.end())
        {
            Command::args_t args;

            std::string temp;
            while (parse >> temp)
            {
                args.push_back(temp);
            }

            responce = &command_iter->second.exec(args);
        }
        else
        {
            responce = &RESP_UNKNOWN_COMMAND;
        }

    }

    return *responce;
}
