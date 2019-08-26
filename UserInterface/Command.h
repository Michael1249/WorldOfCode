#ifndef COMMAND_H
#define COMMAND_H

#include <type_traits>
#include <memory>
#include <QObject>
#include <QVector>
#include "CommandDelegate.h"
#include "CommandRepresent_source.h"

namespace UI
{

struct ArgInfo
{
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& data);

    QString name;
    QChar short_name;

    QString help_tip = "";
    QString default_value = "";
};

class CommandInfo
{

public:
    CommandInfo() = default;
    CommandInfo(const QByteArray& data);

    QJsonObject toJson() const;
    void fromJson(const QByteArray& data);

    void setName(const QString& pNaame);
    void addArg(const ArgInfo& pArg);
    void setHelpTip(const QString& pHelp_tip);
    void setFlagTrack(bool flag_track);

    const QString& getName() const;
    const QString& getHelpTip() const;
    const QList<ArgInfo>& getArgumentsInfo() const;
    bool getFlagTrack() const;
    bool hasHelpTip() const;

private:
    QJsonArray argumentsToJson() const;
    void argumentsFromJson(const QJsonArray& array);
    QString mName;
    QString mHelp_tip;
    QList<ArgInfo> mArguments;
    bool mFlag_track;
};

class CommandRepresent:public CommandRepresentSimpleSource
{
    Q_OBJECT
public:
    CommandRepresent(const CommandInfo& pInfo);

    const CommandInfo& getInfo() const;
    void setInfo(const CommandInfo& pInfo);

    void callCommand(const QString&);

signals:
    void destroyed(const QString&);

public slots:
    void commandDestroyed_slot();

private:
    static QStringList splitArgsLine(const QString & pArgs_str);
    QVector<QString> parseArgsList(const QStringList& args_list) const;

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

    template<class Obj_t, class MFunc_t>
    Command& link_to(Obj_t* pObj_ptr, MFunc_t pMfunc_ptr);

    void enable();
    void disable(const QString& pReason = "");
    bool isEnable() const;

public slots:
    virtual void exec_slot(const QVector<QString> & pArg_vals);

signals:
    void destroyed();

private:

    QString pName;
    std::unique_ptr<ICommandDelegate> mDelegate;

    bool mIs_enable = true;
    QString mDisable_reason;
};

template<class Obj_t, class MFunc_t>
Command &Command::link_to(Obj_t *pObj_ptr, MFunc_t pMfunc_ptr)
{
    mDelegate = getCommandDelegate(pObj_ptr, pMfunc_ptr);
    return *this;
}

} //UI

#endif // COMMAND_H
