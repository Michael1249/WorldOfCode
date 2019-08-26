#ifndef WORKER_H
#define WORKER_H

#include "InterfaceBase.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(UI::InterfaceBase* pInterface, const QString& pName);

private:
    void do_work(const QString& pWork);

    QString mName;

};

#endif // WORKER_H
