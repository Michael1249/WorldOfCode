#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QMap>
#include <QString>
#include "command.h"

namespace UserInterface
{

class CommandParser
{
public:
    using command_map = QMap<QString, Command>;

    CommandParser() = default;

    void add_command(const Command& pCommand);
    void parse_string(const QString& pCommand_str);

private:
    command_map mCommands;
};

} // UserInterface

#endif // COMMANDPARSER_H
