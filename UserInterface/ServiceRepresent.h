#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <memory>
#include <QMap>
#include <QSharedPointer>
#include <QString>
#include "Command.h"

namespace UI
{

class ServiceRepresent: public QObject
{
    Q_OBJECT

public:

    using CommandMap = std::map<QString, std::unique_ptr<CommandRepresent>>;

    ServiceRepresent(const QString& pName, const QString& pHelp_tip = "");

    CommandRepresent* addCommand(const CommandInfo& pInfo);
    void processCommand(const QString& pCommand_str);

    const CommandMap& getCommands() const;

public slots:
    void removeCommand_slot(const QString &pCommand_name);

private:

    QString mName;
    QString mHelpTip;
    CommandMap mCommands;

};

} // UI

#endif // COMMANDPARSER_H
