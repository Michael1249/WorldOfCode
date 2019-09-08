#ifndef LOCALINTERFACE_H
#define LOCALINTERFACE_H

#include <QCoreApplication>
#include <QThread>
#include "InterfaceBase.h"
#include "ServiceRepresent.h"
#include "Interface_source.h"
#include "GlobalService.h"

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

    using ServiceRepresentMap = std::map<QString, std::unique_ptr<ServiceRepresent>>;

    LocalInterface(QCoreApplication *pApp);
    ~LocalInterface();

public slots:
    void run_slot();
    void processCommand_slot(const QString& pLine);
    void sync();
    void quit();

private slots:
    virtual void addRemoteCommand_slot(const QString& pService_name, const QByteArray& pInfo);
    virtual void addService_slot(const QString& pName, const QString& pHelp_tip);
    virtual void removeService_slot(const QString& pName);
    void disableRemoting(QObject* pObj);

signals:
    void listenForInput_signal();
    void finished_signal();

private:

    virtual void connectSyncSignal(ServiceBase* pServise);
    virtual void connectSyncSignal(Command* pCommand);
    virtual void addExistCommand(Command* pCommand);
    void listenForInput();

    void init_remoting();

    QScopedPointer<GlobalService> mGlobal_service;
    QRemoteObjectHost* mHost_node;
    QThread input_thread;
    ServiceRepresentMap mService_represents;
    bool mFlag_run_end = false;

};

} // UI

#endif // LOCALINTERFACE_H
