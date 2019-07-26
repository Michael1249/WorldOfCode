#include <QStringList>
#include <QtDebug>
#include "interface.h"
#include "qiostream.h"
#include "command.h"

namespace UI
{
namespace User
{

Command::Command(Command &&temp):
    mName(std::move(temp.mName)),
    mHelp_tip(std::move(temp.mHelp_tip)),
    mArguments(temp.mArguments),
    mAdapter(std::move(temp.mAdapter)),
    mFlag_track_enable_state(temp.mFlag_track_enable_state),
    mDisable_reason(std::move(temp.mDisable_reason))
{
    Interface::getInstance()->addCommand(*this);
}

Command::Command(const QString pName, bool pTrack_enable_state):
    mName(pName),
    mFlag_track_enable_state(pTrack_enable_state)
{
    Interface::getInstance()->addCommand(*this);

    if(mFlag_track_enable_state)
    {
        qio::qout << '+' << getName() << endl;
    }
}

Command::Command(std::unique_ptr<ICommandDelegate> pAdapter,
                 const QString& pName,
                 const QList<ArgInfo>& pArguments,
                 const QString& pHelp_tip,
                 bool pTrack_enable_state):
    mName(pName),
    mHelp_tip(pHelp_tip),
    mArguments(pArguments),
    mAdapter(std::move(pAdapter)),
    mFlag_track_enable_state(pTrack_enable_state)
{
    Interface::getInstance()->addCommand(*this);

    if(mFlag_track_enable_state)
    {
        qio::qout << '+' << getName() << endl;
    }
}

Command::~Command()
{
    Interface::getInstance()->removeCommand(*this);
    if(mFlag_track_enable_state)
    {
        qio::qout << '-' << getName() << endl;
    }
}

Command &Command::setAdapter(std::unique_ptr<ICommandDelegate> pAdapter)
{
    mAdapter = std::move(pAdapter);
    return *this;
}

Command &Command::addArg(const ArgInfo &pArg)
{
    mArguments.append(pArg);
    return *this;
}

Command &Command::addHelpTip(const QString &pHelp_tip)
{
    mHelp_tip = pHelp_tip;
    return *this;
}

Command &Command::addDisableReason(const QString &pReason)
{
    mDisable_reason = pReason;
    return *this;
}

void Command::exec(const QString &pArgs) const
{

    if(mIs_enable)
    {
        QStringList arg_list = splitArgsLine(pArgs);

        try
        {
            QVector<QString> val_list = parseArgLine(arg_list);
            mAdapter.get()->Invoke(val_list);
        }
        catch (QExceptionMessage& e)
        {
            qio::qout << "[ERROR]: " << e.getMessage() << endl;
        }
        catch (std::exception& e)
        {
            qio::qout << "[ERROR]: " << e.what() << endl;
        }

    }
    else
    {
        qio::qout << mDisable_reason << endl;
    }

}

void Command::enable()
{
    mIs_enable = true;
}

void Command::disable(const QString &pReason)
{
    if(pReason.size())
    {
        mDisable_reason = pReason;
    }
    else
    {
        mDisable_reason = "command disabled";
    }

    mIs_enable = false;
}

bool Command::isEnable() const
{
    return mIs_enable;
}

const QString& Command::getName() const
{
    return mName;
}

const QString &Command::getHelpTip() const
{
    return mHelp_tip;
}

const QList<ArgInfo> &Command::getArgumentsInfo() const
{
    return mArguments;
}

bool Command::hasHelpTip() const
{
    return mHelp_tip.size();
}

QStringList Command::splitArgsLine(const QString &pArgs_str)
{
    QStringList list;
    QString arg;
    bool escape = false;
    enum { Idle, Arg, QuotedArg } state = Idle;
    foreach (QChar const c, pArgs_str) {
        if (!escape && c == '\\') { escape = true; continue; }
        switch (state) {
        case Idle:
            if (!escape && c == '"') state = QuotedArg;
            else if (escape || !c.isSpace()) { arg += c; state = Arg; }
            break;
        case Arg:
            if (!escape && c == '"') state = QuotedArg;
            else if (escape || !c.isSpace()) arg += c;
            else { list << arg; arg.clear(); state = Idle; }
            break;
        case QuotedArg:
            if (!escape && c == '"') state = arg.isEmpty() ? Idle : Arg;
            else arg += c;
            break;
        }
        escape = false;
    }
    if (!arg.isEmpty()) list << arg;
    return list;
}

QString removeBrackets(const QString& pStr)
{
    QString result;
    if(pStr.startsWith('"') && pStr.endsWith('"'))
    {
        result = pStr.mid(1, pStr.size() - 2);
    }
    else
    {
        result = pStr;
    }
    return result;
}

QVector<QString> Command::parseArgLine(const QStringList &args_list) const
{
    QVector<QString> values;
    QVector<bool> setted_values;
    values.resize(mArguments.size());
    setted_values.resize(mArguments.size());
    bool flag_ban_positional = false;

    for (int i = 0; i < args_list.size(); ++i)
    {
        const QString& current_arg = args_list[i];

        if(current_arg.startsWith('-'))
        {
            flag_ban_positional = true;
            QString name = current_arg.section('=', 0, 0).remove('-');
            QString val = current_arg.section('=', 1);

            int arg_pos = -1;
            for (int j = 0; j < mArguments.size(); ++j)
            {
                if(name == mArguments[j].name || name == mArguments[j].short_name)
                {
                    arg_pos = j;
                    break;
                }
            }
            if(arg_pos != -1)
            {
                values[arg_pos] = val.size() ? removeBrackets(val) : mArguments[arg_pos].default_value;
                setted_values[arg_pos] = true;
            }
            else
            {
                throw QExceptionMessage("Unknown argument name <" + name + '>' );
            }

        }
        else
        {
            if(!flag_ban_positional)
            {
                values[i] = current_arg.size() ? removeBrackets(current_arg) : mArguments[i].default_value;
                setted_values[i] = true;
            }
            else
            {
                throw QExceptionMessage("Positional argument \"" + current_arg
                                        + "\" must be placed before nemed argument(s)" );
            }
        }
    }

    for (int i = 0; i < setted_values.size(); ++i)
    {
        if(!setted_values[i])
            values[i] = mArguments[i].default_value;
    }

    return values;
}

} // User
} // UI
