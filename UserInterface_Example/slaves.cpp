#include "slaves.h"
#include "qiostream.h"

Slaves::Slaves(UI::InterfaceBase *interface, const QString &name):
    UI::ServiceBase (interface, name, "This is slaves")
{
    UI::CommandInfo buy_cmd_info;
    buy_cmd_info.setName("buy");
    buy_cmd_info.setHelpTip("You can buy new slave!");
    buy_cmd_info.addArg(
        UI::ArgInfo
        {
            .name="name",
            .short_name = 'n',
            .help_tip = "slave name."
        }
    );

    UI::CommandInfo kill_cmd_info;
    kill_cmd_info.setName("kill");
    kill_cmd_info.setHelpTip("You can kiil your slave!");
    kill_cmd_info.addArg(
        UI::ArgInfo
        {
            .name="name",
            .short_name = 'n',
            .help_tip = "slave name."
        }
    );

    UI::CommandInfo order_cmd_info;
    order_cmd_info.setName("order");
    order_cmd_info.setHelpTip("You can order your slave to work!");
    order_cmd_info.addArg(
        UI::ArgInfo
        {
            .name="name",
            .short_name = 'n',
            .help_tip = "slave name."
        }
    );
    order_cmd_info.addArg(
        UI::ArgInfo
        {
            .name="work",
            .short_name = 'w',
            .help_tip = "kind of work",
            .default_value = "money for you"
        }
    );

    addCommand(this, &Slaves::buy_slave_cmd, buy_cmd_info);
    addCommand(this, &Slaves::kill_slave_cmd, kill_cmd_info);
    addCommand(this, &Slaves::order_cmd, order_cmd_info);
}

void Slaves::buy_slave_cmd(const QString &name)
{
    if(slaves.contains(name))
    {
        qio::qout << QString("You bougt new slave, %1! Old %1 died of hunger").arg(name) << endl;
    }
    else
    {
        slaves.append(name);
        qio::qout << QString("You bougt new slave, %1!").arg(name) << endl;
    }
}

void Slaves::kill_slave_cmd(const QString &name)
{
    if(slaves.contains(name))
    {
        slaves.removeOne(name);
        qio::qout << QString("You killed %1. You are monster!").arg(name) << endl;
    }
    else
    {
        qio::qout << QString("You don't have slave named %1!").arg(name) << endl;
    }
}

void Slaves::order_cmd(const QString &name, const QString &work)
{
    if(slaves.contains(name))
    {
        qio::qout << QString("%1 is doing the %2 now.").arg(name).arg(work) << endl;
    }
    else
    {
        qio::qout << QString("You don't have slave named %1!").arg(name) << endl;
    }
}
