#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QMap>
#include <QString>
#include <memory.h>
#include "command.h"

namespace UI
{

class CommandParser
{
public:
    using command_map = QMap<QString,const Command*>;

    CommandParser() = default;

    void addCommand(const Command& pCommand);
    void removeCommand(const Command& pCommand);
    void parseString(const QString& pCommand_str);

private:
    command_map mCommands;
};

} // UserInterface

#endif // COMMANDPARSER_H
