#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <memory.h>
#include "commandadapter.h"

namespace UI
{
class Command
{
public:
    struct ArgInfo
    {
        QString arg_name;
        QChar arg_short_name;
        QString help_tip = "";
        QString default_value = "";

    };

    Command(std::unique_ptr<ICommandDelegate> pAdapter,
            const QString& pName,
            const QList<ArgInfo>& pSignature,
            const QString& pHelp_tip);

    void exec(const QString& pArgs) const;

    void setEnable(bool pEnable);
    bool isEnable() const;

    const QString& getName() const;
    const QString& getHelpTip() const;
    const QList<ArgInfo>& getArgumentsInfo() const;
    bool hasHelpTip() const;

private:
    static QStringList splitArgsLine(const QString & pArgs_str);
    QVector<QString> parse(const QStringList& args_list) const;

    QString mName;
    QString mHelp_tip;
    bool mIs_enable = true;
    QList<ArgInfo> mSignature;
    std::unique_ptr<ICommandDelegate> mAdapter;
};

} //UserInterface

#endif // COMMAND_H
