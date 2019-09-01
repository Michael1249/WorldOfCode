#include "worker.h"
#include "qiostream.h"
#include "QTimer"

Worker::Worker(UI::InterfaceBase *pInterface, const QString &pName):
    UI::ServiceBase (pInterface, "slaves"),
    mName(pName)
{
    UI::CommandInfo info;
    info.setName(pName);
    info.setHelpTip(QString("I'm worker, my name is %1. Tell me if you need to do something").arg(pName));
    info.addArg(
            UI::ArgInfo
            {
                .name="work",
                .short_name = 'w',
                .help_tip = "work to be done.",
                .default_value = "sleep"
            }
        );
    addCommand(this, &Worker::do_work, info);
}

void Worker::do_work(const QString &pWork)
{

    if(pWork == "sleep")
    {
        qio::qout << QString("Now %1 is sleeping.").arg(mName) << endl;
    }
    else
    {
        qio::qout << QString("Now %1 is working on %2.").arg(mName).arg(pWork) << endl;
    }

}
