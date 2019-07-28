#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <QVector>
#include "CommandDelegate.h"

namespace UI
{

struct ArgInfo
{
    QString name;
    QChar short_name;

    QString help_tip = "";
    QString default_value = "";
};

/*
Represetn interface between User (Input) and c++ function

Provide to call function with user's input string line

Note: each argument of function must to be able to initializate by QString object
*/
class Command
{

public:

    Q_DISABLE_COPY_MOVE(Command)
    Command(const QString pName, std::unique_ptr<ICommandDelegate> pDelegate , bool pTrack = true);

    ~Command();

    Command& addArg(const ArgInfo& pArg);
    Command& addHelpTip(const QString& pHelp_tip);

    void exec(const QString& pArgs) const;

    void enable();
    void disable(const QString& pReason = "");
    bool isEnable() const;

    const QString& getName() const;
    const QString& getHelpTip() const;
    const QList<ArgInfo>& getArgumentsInfo() const;
    bool hasHelpTip() const;

private:

    static QStringList splitArgsLine(const QString & pArgs_str);
    QVector<QString> parseArgLine(const QStringList& args_list) const;

    QString mName;
    QString mHelp_tip;
    QList<ArgInfo> mArguments;
    std::unique_ptr<ICommandDelegate> mDelegate;

    bool mIs_enable = true;
    QString mDisable_reason;

    //if true, track creation and destruction and output to console
    bool mFlag_track;
};

} //UI

#endif // COMMAND_H
