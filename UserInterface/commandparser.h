#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QMap>
#include <QString>
#include "command.h"

namespace UserInterface
{

class CommandParser
{
    using command_map = QMap<QString, Command>;

public:
    CommandParser() = default;

    void add_command(const Command& pCommand);
    void parse_string(const QString& pCommand_str);

private:
    command_map mCommands;
};

} // UserInterface

#endif // COMMANDPARSER_H
