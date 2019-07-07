#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>
#include <QVector>
#include "commandadapter.h"

namespace UserInterface
{

class Command
{
public:
    Command() = default;

    void exec(const QString& pArgs);
    const QString& getName() const;

private:
    struct ArgumentInfo
    {
        QString help;
        QString name;
        QChar opt_name;
        QString default_value;
    };

    QString mName;
    QString mHelp;
    QVector<ArgumentInfo> mArgs_info;

    ICommandAdapter* mAdapter;
};

} //UserInterface

#endif // COMMAND_H
