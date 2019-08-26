#ifndef WORKER_H
#define WORKER_H

#include "InterfaceBase.h"

class Worker
{
public:
    Worker(UI::InterfaceBase* pInterface, const QString& pName);

private:
    void do_work(const QString& pWork);
    UI::Command do_work_command;

    QString mName;

};

#endif // WORKER_H
