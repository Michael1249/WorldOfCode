#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <memory>
#include <QMap>
#include <QPointer>
#include <QString>
#include "Command.h"

namespace UI
{

class CommandParser
{
public:

    using command_map = QMap<QString, QPointer<CommandRepresent>>;

    CommandParser() = default;

    CommandRepresent* addCommand(const CommandInfo& pInfo);
    void removeCommand(const QString &pCommand_name);
    void parseString(const QString& pCommand_str);

    const command_map& getCommands() const;

private:

    command_map mCommands;

};

} // UI

#endif // COMMANDPARSER_H
