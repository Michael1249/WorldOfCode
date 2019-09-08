#ifndef COMMANDREPRESENT_H
#define COMMANDREPRESENT_H

#include "CommandInfo.h"
#include "CommandRepresent_source.h"

namespace UI
{
class CommandRepresent:public CommandRepresentSimpleSource
{
    Q_OBJECT
public:
    CommandRepresent(const CommandInfo& pInfo);

    const CommandInfo& getInfo() const;
    void setInfo(const CommandInfo& pInfo);

    void execCommand(const QString& pArgs_line);

signals:
    void commandDestroyed_signal(const QString&);

public slots:
    void commandDestroyed_slot();

private:
    static QStringList splitArgsLine(const QString & pArgs_str);
    QVector<QString> parseArgsList(const QStringList& pArgs_list) const;

    CommandInfo mInfo;
};


} //UI


#endif // COMMANDREPRESENT_H
