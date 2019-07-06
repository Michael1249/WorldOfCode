#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>
class Command
{
public:
    Command() = default;
    virtual ~Command() = default;

    void exec(const QString& pArgs);
    const QString& getName() const;

private:
    virtual void call_cxx_function(const QStringList& pArg_list);

    QString mName;
};

#endif // COMMAND_H
