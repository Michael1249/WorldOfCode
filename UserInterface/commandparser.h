#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <map>
#include <string>
#include "command.h"

class CommandParser
{
    using command_map = std::map<std::string, Command>;

public:
    const std::string RESP_EMPTY_STRING = "";
    const std::string RESP_UNKNOWN_COMMAND = "";

    CommandParser() = default;

    void add_command(const Command& pCommand);
    const std::string& parse_string(const std::string& pCommand_str);

private:
    command_map mCommands;
};

#endif // COMMANDPARSER_H
