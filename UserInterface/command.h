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
    QString help;
    QVector<ArgumentInfo> args_info;

    ICommandAdapter* adapter;
};

} //UserInterface

#endif // COMMAND_H
