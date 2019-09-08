#include "CommandRepresent.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "qiostream.h"

namespace UI
{

// NOT MY CODE
QStringList CommandRepresent::splitArgsLine(const QString& pArgs_str)
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

QVector<QString> CommandRepresent::parseArgsList(const QStringList &pArgs_list) const
{
    QVector<QString> values;
    QVector<bool> setted_values;
    values.resize(mInfo.getArgumentsInfo().size());
    setted_values.resize(mInfo.getArgumentsInfo().size());
    bool flag_ban_positional = false;

    for (int i = 0; i < pArgs_list.size(); ++i)
    {
        const QString& current_arg = pArgs_list[i];

        if(current_arg.startsWith('-'))
        {
            flag_ban_positional = true;
            QString name = current_arg.section('=', 0, 0).remove('-');
            QString val = current_arg.section('=', 1);

            int arg_pos = -1;
            for (int j = 0; j < mInfo.getArgumentsInfo().size(); ++j)
            {

                if(name == mInfo.getArgumentsInfo()[j].name || name == mInfo.getArgumentsInfo()[j].short_name)
                {
                    arg_pos = j;
                    break;
                }

            }
            if(arg_pos != -1)
            {
                values[arg_pos] = val.size() ?
                            removeBrackets(val) :
                            mInfo.getArgumentsInfo()[arg_pos].default_value;
                setted_values[arg_pos] = true;
            }
            else
            {
                throw QExceptionMessage(ERR_UNKNOWN_ARG.arg(name));
            }

        }
        else
        {
            if(!flag_ban_positional)
            {

                if(i >= values.size())
                {
                    throw QExceptionMessage(ERR_TOO_MANY_ARGS.arg(values.size()));
                }

                values[i] = current_arg.size() ?
                            removeBrackets(current_arg) :
                            mInfo.getArgumentsInfo()[i].default_value;
                setted_values[i] = true;
            }
            else
            {
                throw QExceptionMessage(ERR_INVALID_ARG.arg(current_arg));
            }

        }

    }

    for (int i = 0; i < setted_values.size(); ++i)
    {

        if(!setted_values[i])
        {
            values[i] = mInfo.getArgumentsInfo()[i].default_value;
        }

    }
    return values;
}

void CommandRepresent::commandDestroyed_slot()
{
    emit commandDestroyed_signal(mInfo.getName());
}

CommandRepresent::CommandRepresent(const CommandInfo &pInfo):
    mInfo(pInfo)
{
}

const CommandInfo &CommandRepresent::getInfo() const
{
    return mInfo;
}

void CommandRepresent::setInfo(const CommandInfo& pInfo)
{
    mInfo = pInfo;
}

void CommandRepresent::execCommand(const QString& pArgs_line)
{
    try
    {
        auto args_list = splitArgsLine(pArgs_line);
        auto arg_vals = parseArgsList(args_list);
        emit exec_signal(arg_vals);
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

} // UI
