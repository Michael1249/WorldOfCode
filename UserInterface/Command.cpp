#include "LocalInterface.h"
#include "qiostream.h"
#include "qexceptionmessage.h"
#include "UIConstants.h"
#include "Command.h"
#include "ServiceBase.h"


namespace UI
{

Command::Command(QObject *parent, CommandInfo pInfo, ServiceBase *pService):
    QObject (parent),
    mInfo(pInfo),
    mService(pService)
{
}

Command::~Command()
{
    emit destroyed_signal();
}

const CommandInfo &Command::getInfo() const
{
    return mInfo;
}

const ServiceBase *Command::getService() const
{
    return mService;
}

const QString& Command::getServiceName() const
{
    return mService ? mService->getName() : GLOBAL_SERVICE_NAME;
}

void Command::exec_slot(const QVector<QString> &pArg_vals)
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

} // UI
