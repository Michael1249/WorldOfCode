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
    void run_slot();
    void processCommand_slot(const QString& pLine);

private slots:
    virtual void addRemoteCommand_slot(const QString& pService_name, const QByteArray& pInfo);
    virtual void addService_slot(const QString& pName, const QString& pHelp_tip);
    virtual void removeService_slot(const QString& pName);

signals:
    void listenForInput_signal();
    void finished_signal();

private:
    virtual void addService(ServiceBase* pServise);
    virtual void addExistCommand(const QString& pService_name, Command& pCommand, const CommandInfo& pInfo);
    void listenForInput();

    // commands
    void help_cmd(const QString& pStr);
    void sync_cmd();

    void init_help_cmd();
    void init_sync_cmd();

    void init_remoting();

    QRemoteObjectHost* mHost_node;
    QThread input_thread;
    ServiceRepresentMap mServices;
    bool mFlag_run_end = false;

};

} // UI

#endif // LOCALINTERFACE_H
