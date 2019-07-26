#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <QStringList>
#include <QVector>
#include "CommandDelegate.h"
#include "qexceptionmessage.h"

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

    Q_DISABLE_COPY(Command)
    Command(Command&& temp);
    Command(const QString pName, bool pTrack = true);
    Command(std::unique_ptr<ICommandDelegate> pAdapter,
            const QString& pName,
            const QList<ArgInfo>& pArguments,
            const QString& pHelp_tip,
            bool pTrack = true);
    ~Command();

    /*
    methods for easy Command initialization
    with explicit indication of the arguments passed
    */
    Command& addArg(const ArgInfo& pArg);
    Command& addHelpTip(const QString& pHelp_tip);
    Command& addDisableReason(const QString& pReason);
    Command& linkTo(std::unique_ptr<ICommandDelegate> pAdapter);
    template<class Obj_t, class Mfunc_t>
    Command& linkTo(Obj_t* pObj, Mfunc_t pMfunc);

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
    std::unique_ptr<ICommandDelegate> mAdapter;

    bool mIs_enable = true;
    QString mDisable_reason;

    //if true, track creation and destruction and output to console
    bool mFlag_track;
};

template<class Obj_t, class Mfunc_t>
Command &Command::linkTo(Obj_t *pObj, Mfunc_t pMfunc)
{
    mAdapter = std::move(getCommandDelegate(pObj, pMfunc));
    return *this;
}

} //UI

#endif // COMMAND_H
