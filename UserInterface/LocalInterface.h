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
    void newLineDetected_signal(const QString& pLine);
public slots:
    void listenForInput_slot();
};

class LocalInterface : public InterfaceSimpleSource, public InterfaceBase
{
    Q_OBJECT

public:
    LocalInterface(QCoreApplication *pApp);
    ~LocalInterface();

public slots:
    virtual void addCommand_slot(Command& pCommand, const CommandInfo& pInfo);
    virtual void addRemoteCommand_slot(const QByteArray& pInfo);
    virtual void removeCommand_slot(const QString &pCommand_name);
    void run_slot();
    void processLine_slot(const QString& pLine);

signals:
    void listenForInput_signal();
    void finished_signal();

private:
    void listenForInput();

    // commands
    void help_request(const QString& pStr);

    QRemoteObjectHost* mHost_node;
    QThread input_thread;
    CommandParser mParser;
    bool mFlag_run_end = false;

};

} // UI

#endif // INTERFACE_H
