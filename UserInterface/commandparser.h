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
    using command_map = QMap<QString,const User::Command*>;

    CommandParser() = default;

    void addCommand(const User::Command& pCommand);
    void removeCommand(const User::Command& pCommand);
    void parseString(const QString& pCommand_str);

    const command_map& getCommands() const;
    command_map getActiveCommands() const;

private:
    command_map mCommands;
};

} // UserInterface

#endif // COMMANDPARSER_H
