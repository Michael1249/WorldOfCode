#include <QJsonArray>
#include <QJsonDocument>
#include "CommandInfo.h"

namespace UI
{

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

void CommandInfo::argumentsFromJson(const QJsonArray &pArray)
{
    mArguments.clear();
    for (const auto& iter : pArray)
    {
        mArguments.append(ArgInfo());
        mArguments.last().fromJson(iter.toObject());
    }
}

bool CommandInfo::getFlagTrack() const
{
    return mFlag_track;
}

void CommandInfo::setFlagTrack(bool pFlag_track)
{
    mFlag_track = pFlag_track;
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

void ArgInfo::fromJson(const QJsonObject &pData)
{
    name = pData["name"].toString();
    short_name = pData["short_name"].toString()[0];
    help_tip = pData["help_tip"].toString();
    default_value = pData["default_value"].toString();
}

} // UI
