#ifndef SLAVES_H
#define SLAVES_H

#include "ServiceBase.h"

class Slaves : public UI::ServiceBase
{
    Q_OBJECT

public:
    Slaves(UI::InterfaceBase* interface, const QString& name);

    void buy_slave_cmd(const QString& name);
    void kill_slave_cmd(const QString& name);
    void order_cmd(const QString& name, const QString& work);

private:
    QStringList slaves;
};

#endif // SLAVES_H
