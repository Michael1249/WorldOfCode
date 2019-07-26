#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <memory>
#include <QMap>
#include <QString>
#include "Command.h"

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

    const command_map& getCommands() const;
    command_map getActiveCommands() const;

private:

    command_map mCommands;

};

} // UserInterface

#endif // COMMANDPARSER_H
