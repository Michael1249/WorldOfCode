#ifndef INTERFACE_H
#define INTERFACE_H

#include <QCoreApplication>
#include <QThread>
#include "InterfaceBase.h"
#include "CommandParser.h"
#include "Interface_source.h"

namespace UI
{

class InputReader: public QObject
{
    Q_OBJECT

signals:
    void newLineDetected_signal(const QString& line);
public slots:
    void listenForInput_slot();
};

class LocalInterface : public InterfaceSimpleSource, public InterfaceBase
{
    Q_OBJECT

public:
    LocalInterface(QCoreApplication *parent);
    ~LocalInterface();
    void listenForInput();

public slots:
    virtual void addCommand_slot(Command& pCommand, const CommandInfo& pInfo);
    virtual void addRemoteCommand_slot(const QByteArray& pInfo);
    virtual void removeCommand_slot(const QString &pCommand_name);
    virtual void test();
    void run_slot();
    void processLine_slot(const QString& line);

signals:
    void listenForInput_signal();
    void finished_signal();

private:
    friend class Command;

    // commands
    void help_request(const QString& pStr);
    Command mHelp_request_cmd;

    QRemoteObjectHost* mHost_node;
    QThread input_thread;
    CommandParser mParser;
    bool mFlag_run_end = false;

};

} // UI

#endif // INTERFACE_H
