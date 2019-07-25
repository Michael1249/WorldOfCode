#ifndef COMMAND_H
#define COMMAND_H

#include <memory.h>
#include <QString>
#include <QStringList>
#include <QVector>
#include "commandadapter.h"
#include "qexceptionmessage.h"

namespace UI
{
namespace User
{

struct ArgInfo
{
    QString name;
    QChar short_name;
    QString help_tip = "";
    QString default_value = "";

};

class Command
{
public:

    Command(Command&& temp);
    Command(const QString pName, bool pTrack_enable_state = true);
    Command(std::unique_ptr<ICommandDelegate> pAdapter,
            const QString& pName,
            const QList<ArgInfo>& pArguments,
            const QString& pHelp_tip,
            bool pTrack_enable_state = true);
    ~Command();

    Command& addArg(const ArgInfo& pArg);
    Command& addHelpTip(const QString& pHelp_tip);
    Command& addDisableReason(const QString& pReason);

    Command& setAdapter(std::unique_ptr<ICommandDelegate> pAdapter);
    template<class Obj_t, class Mfunc_t>
    Command& setAdapter(Obj_t* pObj, Mfunc_t pMfunc)
    {
        mAdapter = std::move(getCommandDelegate(pObj, pMfunc));
        return *this;
    }

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
    bool mFlag_track_enable_state;
    QString mDisable_reason = "";
};

} //User
} //UI

#endif // COMMAND_H
