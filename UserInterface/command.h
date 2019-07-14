#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <memory.h>
#include "commandadapter.h"


namespace UserInterface
{
class Command
{
public:
    using Delegate_ptr_t = std::unique_ptr<ICommandDelegate>;
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
            Delegate_ptr_t pAdapter);

    void exec(const QString& pArgs) const;
    const QString& getName() const;

private:
    static QStringList splitArgsLine(const QString & pArgs_str);

    QString mName;
    QString mHelp;
    QVector<ArgumentInfo> mArgs_info;

    Delegate_ptr_t mAdapter;
};

} //UserInterface

#endif // COMMAND_H
