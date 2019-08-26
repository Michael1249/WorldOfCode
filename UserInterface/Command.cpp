#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "LocalInterface.h"
#include "qiostream.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "Command.h"


namespace UI
{

Command::~Command()
{
    emit destroyed();
}

void Command::enable()
{
    mIs_enable = true;
}

void Command::disable(const QString& pReason)
{
    if(pReason.size())
    {
        mDisable_reason = pReason;
    }
    else
    {
        mDisable_reason = CMD_DISABLE_REASON;
    }

    mIs_enable = false;
}

bool Command::isEnable() const
{
    return mIs_enable;
}

void Command::exec_slot(const QVector<QString> &pArg_vals)
{
    if(mIs_enable)
    {

        try
        {
            mDelegate.get()->Invoke(pArg_vals);
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

QVector<QString> CommandRepresent::parseArgsList(const QStringList &args_list) const
{
    QVector<QString> values;
    QVector<bool> setted_values;
    values.resize(mInfo.getArgumentsInfo().size());
    setted_values.resize(mInfo.getArgumentsInfo().size());
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
    emit destroyed(mInfo.getName());
}

CommandInfo::CommandInfo(const QByteArray &data)
{
    fromJson(data);
}

QJsonObject CommandInfo::toJson() const
{
    QJsonObject json;
    json["name"] = mName;
    json["help_tip"] = mHelp_tip;
    json["arguments"] = argumentsToJson();
    json["flag_track"] = mFlag_track;
    return json;
}

void CommandInfo::fromJson(const QByteArray &data)
{
    QJsonObject json = QJsonDocument::fromJson(data).object();
    mName = json["name"].toString();
    mHelp_tip = json["help_tip"].toString();
    argumentsFromJson(json["arguments"].toArray());
    mFlag_track = json["flag_track"].toBool();
}

void CommandInfo::setName(const QString &pNaame)
{
    mName = pNaame;
}

void CommandInfo::addArg(const ArgInfo &pArg)
{
    mArguments.append(pArg);
}

void CommandInfo::setHelpTip(const QString &pHelp_tip)
{
    mHelp_tip = pHelp_tip;
}

const QString &CommandInfo::getName() const
{
    return mName;
}

const QString &CommandInfo::getHelpTip() const
{
    return mHelp_tip;
}

const QList<ArgInfo> &CommandInfo::getArgumentsInfo() const
{
    return mArguments;
}

bool CommandInfo::hasHelpTip() const
{
    return mHelp_tip.size();
}

QJsonArray CommandInfo::argumentsToJson() const
{
    QJsonArray array;
       for (const auto& arg_info : mArguments)
          array.append(arg_info.toJson());
       return array;
}

void CommandInfo::argumentsFromJson(const QJsonArray &array)
{
    auto iter = array.begin();
    for (auto& arg_info : mArguments)
       arg_info.fromJson(iter->toObject());
}

bool CommandInfo::getFlagTrack() const
{
    return mFlag_track;
}

void CommandInfo::setFlagTrack(bool flag_track)
{
    mFlag_track = flag_track;
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

void CommandRepresent::callCommand(const QString& pArgs)
{
    try
    {
        auto args_list = splitArgsLine(pArgs);
        auto arg_vals = parseArgsList(args_list);
        emit call_signal(arg_vals);
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

QJsonObject ArgInfo::toJson() const
{
    QJsonObject json;
    json["name"] = name;
    json["short_name"] = QString(short_name);
    json["help_tip"] = help_tip;
    json["default_value"] = default_value;
    return json;
}

void ArgInfo::fromJson(const QJsonObject &data)
{
    name = data["name"].toString();
    short_name = data["short_name"].toString()[0];
    help_tip = data["help_tip"].toString();
    default_value = data["default_value"].toString();
}

} // UI
