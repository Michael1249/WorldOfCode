#include <QStringList>
#include <QtDebug>
#include "command.h"

namespace UI
{

Command::Command(std::unique_ptr<ICommandDelegate> pAdapter,
                 const QString& pName,
                 const QList<ArgInfo>& pSignature,
                 const QString& pHelp_tip):
    mName(pName),
    mHelp_tip(pHelp_tip),
    mSignature(pSignature),
    mAdapter(std::move(pAdapter))
{

}

void Command::exec(const QString &pArgs) const
{

    if(mIs_enable)
    {
        QStringList arg_list = splitArgsLine(pArgs);
        QVector<QString> val_list = parse(arg_list);

        mAdapter.get()->Invoke(val_list);
    }

}

void Command::setEnable(bool pEnable)
{
    mIs_enable = pEnable;
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

const QList<Command::ArgInfo> &Command::getArgumentsInfo() const
{
    return mSignature;
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

QVector<QString> Command::parse(const QStringList &args_list) const
{
    QVector<QString> vals_list;
    QVector<bool> setted_vals;
    vals_list.resize(mSignature.size());
    setted_vals.resize(mSignature.size());
    bool ban_positional = false;

    for (int i = 0; i < args_list.size(); ++i)
    {
        const QString& current_arg = args_list[i];

        if(current_arg.startsWith('-'))
        {
            ban_positional = true;
            QString name = current_arg.section('=', 0, 0).remove('-');
            QString val = current_arg.section('=', 1);

            int arg_pos = -1;
            for (int j = 0; j < mSignature.size(); ++j)
            {
                if(name == mSignature[j].arg_name || name == mSignature[j].arg_short_name)
                {
                    arg_pos = j;
                    break;
                }
            }
            if(arg_pos != -1)
            {
                vals_list[arg_pos] = val.size() ? removeBrackets(val) : mSignature[arg_pos].default_value;
                setted_vals[arg_pos] = true;
            }
            else
            {
                //critical unknown arg name
                qDebug("unknown arg name");
            }

        }
        else
        {
            if(!ban_positional)
            {
                vals_list[i] = current_arg.size() ? removeBrackets(current_arg) : mSignature[i].default_value;
                setted_vals[i] = true;
            }
            else
            {
                qDebug("undefined arg position");//error undefined arg position
            }
        }
    }

    for (int i = 0; i < setted_vals.size(); ++i)
    {
        if(!setted_vals[i])
            vals_list[i] = mSignature[i].default_value;
    }

    return vals_list;
}

} // UserInterface
