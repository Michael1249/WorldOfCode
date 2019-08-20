#ifndef INTERFACE_H
#define INTERFACE_H

#include <QCoreApplication>
#include "CommandParser.h"
#include "Interface_source.h"

namespace UI
{

class Interface : public InterfaceSimpleSource
{
    Q_OBJECT

public:
    Interface(QCoreApplication *parent = nullptr);
    ~Interface() = default;

public slots:
    virtual void addCommand_slot(QString pURL);
    virtual void rmCommand_slot(QString pURL);
    void run();

signals:
    void finished();

private:
    void help_request(const QString& pStr);
    Command mHelp_request_cmd;

    friend class Command;

    void addCommand(const Command& pCommand, const CommandInfo& pInfo);
    void removeCommand(const QString &pCommand_name);

    QRemoteObjectHost mRemote_node;
    CommandParser mParser;
    bool mFlag_run_end = false;

};

} // UI

#endif // INTERFACE_H
