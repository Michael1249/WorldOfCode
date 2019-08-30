#ifndef LOCALINTERFACE_H
#define LOCALINTERFACE_H

#include <QCoreApplication>
#include <QThread>
#include "InterfaceBase.h"
#include "ServiceRepresent.h"
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

    using ServiceRepresentMap = QMap<QString, QPointer<ServiceRepresent>>;

    LocalInterface(QCoreApplication *pApp);
    ~LocalInterface();

public slots:
    virtual void addCommand_slot(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo);
    virtual void addRemoteCommand_slot(const QString& pService_name, const QByteArray& pInfo);
    void run_slot();
    void processCommand_slot(const QString& pLine);

protected slots:
    virtual void addService_slot(const QString& pName, const QString& pHelp_tip);
    virtual void removeService_slot(const QString& pName);

signals:
    void listenForInput_signal();
    void finished_signal();

private:
    void listenForInput();

    // commands
    void help_cmd(const QString& pStr);
    void sync_cmd();

    QRemoteObjectHost* mHost_node;
    QThread input_thread;
    ServiceRepresentMap mServices;
    bool mFlag_run_end = false;

};

} // UI

#endif // LOCALINTERFACE_H
