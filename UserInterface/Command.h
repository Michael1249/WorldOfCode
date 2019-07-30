#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <QObject>
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

class CommandInfo
{
public:
    CommandInfo(const QString& pName);

    void setName(const QString& pNaame);
    void setArg(const ArgInfo& pArg);
    void setHelpTip(const QString& pHelp_tip);

    const QString& getName() const;
    const QString& getHelpTip() const;
    const QList<ArgInfo>& getArgumentsInfo() const;
    bool hasHelpTip() const;

private:
    QString mName;
    QString mHelp_tip;
    QList<ArgInfo> mArguments;
};

class CommandRepresent:public QObject
{
    Q_OBJECT
public:
    CommandRepresent(const CommandInfo& pInfo);

    const CommandInfo& getInfo() const;
    void setInfo(const CommandInfo& pInfo);
    //void copyInfo(); in future for remote commands

signals:
    void exec(const QString&);

private:
    CommandInfo const* mInfo_ptr;
};

/*
Represetn interface between User (Input) and c++ function

Provide to call function with user's input string line

Note: each argument of function must to be able to initializate by QString object
*/
class Command: public QObject
{
    Q_OBJECT

public:

    Q_DISABLE_COPY_MOVE(Command)
    Command(const QString pName, std::unique_ptr<ICommandDelegate> pDelegate , bool pTrack = true);

    ~Command();

    Command& addArg(const ArgInfo& pArg);
    Command& addHelpTip(const QString& pHelp_tip);

    void enable();
    void disable(const QString& pReason = "");
    bool isEnable() const;

    const CommandInfo& getInfo() const;

private slots:
    void exec_slot(const QString& pArgs) const;

private:

    static QStringList splitArgsLine(const QString & pArgs_str);
    QVector<QString> parseArgLine(const QStringList& args_list) const;

    CommandInfo mInfo;
    std::unique_ptr<ICommandDelegate> mDelegate;

    bool mIs_enable = true;
    QString mDisable_reason;

    //if true, track creation and destruction and output to console
    bool mFlag_track;
};

} //UI

#endif // COMMAND_H
