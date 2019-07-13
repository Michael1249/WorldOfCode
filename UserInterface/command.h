#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>
#include <QVector>
#include "commandadapter.h"

namespace UserInterface
{
class ICommandAdapter{};
class Command
{
public:
    struct ArgumentInfo
    {
        QString name;
        QChar opt_name;
        QString help;
        QString default_value;
    };


    Command(const QString& pName,
            const QString& pHelp,
            const QVector<ArgumentInfo>& pArgs_info,
            ICommandAdapter* pAdapter);

    void exec(const QString& pArgs);
    const QString& getName() const;

private:
    QStringList splitArgsLine(const QString & pArgs_str);

    QString mName;
    QString mHelp;
    QVector<ArgumentInfo> mArgs_info;

    ICommandAdapter* mAdapter;
};

} //UserInterface

#endif // COMMAND_H
