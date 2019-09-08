#ifndef COMMANDINFO_H
#define COMMANDINFO_H

#include <QJsonObject>
#include <QList>

namespace UI
{

struct ArgInfo
{
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& pData);

    QString name;
    QChar short_name;

    QString help_tip = "";
    QString default_value = "";
};

class CommandInfo
{

public:
    CommandInfo() = default;
    CommandInfo(const QByteArray& pData);

    // TODO: overwrite "serialization" with operator<< and operator>>
    // instead casting to Json (aka QByteArray)
    QJsonObject toJson() const;
    void fromJson(const QByteArray& pData);

    void setName(const QString& pNaame);
    void addArg(const ArgInfo& pArg);
    void setHelpTip(const QString& pHelp_tip);
    void setFlagTrack(bool pFlag_track);

    const QString& getName() const;
    const QString& getHelpTip() const;
    const QList<ArgInfo>& getArgumentsInfo() const;
    bool getFlagTrack() const;
    bool hasHelpTip() const;

private:
    QJsonArray argumentsToJson() const;
    void argumentsFromJson(const QJsonArray& pArray);
    QString mName;
    QString mHelp_tip;
    QList<ArgInfo> mArguments;
    bool mFlag_track;
};

} // UI

#endif // COMMANDINFO_H
