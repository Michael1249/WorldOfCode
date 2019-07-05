#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <map>
#include <string>
#include "command.h"

class CommandParser
{
    using command_map = std::map<std::string, Command>;

public:
    CommandParser() = default;

    void add_command(const Command& pCommand);
    void parse_string(const std::string& pCommand_str);

private:
    command_map mCommands;
};

#endif // COMMANDPARSER_H
