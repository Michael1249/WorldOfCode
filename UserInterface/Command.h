#ifndef COMMAND_H
#define COMMAND_H

#include <type_traits>
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

signals:
    void exec(const QString&);

private:
    CommandInfo mInfo;
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
    Command() = default;
    ~Command();

    Command& setName(const QString& pName);
    Command& addArg(const ArgInfo& pArg);
    Command& setHelpTip(const QString& pHelp_tip);
    template<class Obj_t, class MFunc_t>
    Command& link_to(Obj_t* pObj_ptr, MFunc_t pMfunc_ptr);
    void addToUI(bool pTrack = true);

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

template<class Obj_t, class MFunc_t>
Command &Command::link_to(Obj_t *pObj_ptr, MFunc_t pMfunc_ptr)
{
    mDelegate = getCommandDelegate(pObj_ptr, pMfunc_ptr);
    return *this;
}

} //UI

#endif // COMMAND_H
