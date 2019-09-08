#include "LocalInterface.h"
#include "GlobalService.h"
#include "UIConstants.h"

namespace UI
{

GlobalService::GlobalService(LocalInterface *interface):
    ServiceBase (static_cast<InterfaceBase*>(interface), GLOBAL_SERVICE_NAME)
{
    init_help_cmd();
    init_sync_cmd();
    init_quit_cmd();
}

void GlobalService::init_help_cmd()
{
    CommandInfo info;
    info.setName("help");
    info.setHelpTip("helps to find command and get discription");
    info.addArg(
            ArgInfo
            {
                .name="filter",
                .short_name = 'f',
                .help_tip = "search for commands which contain <filter>,\n"
                            "show command's details if it's found."
            }
        );
   addCommand(this, &GlobalService::help_cmd, info);
}

void GlobalService::init_sync_cmd()
{
    CommandInfo info;
    info.setName("sync");
    info.setHelpTip("Synchronize data from existing services.");
    addCommand(static_cast<LocalInterface*>(getInterface()), &LocalInterface::sync, info);
}

void GlobalService::init_quit_cmd()
{
    CommandInfo info;
    info.setName("quit");
    info.setHelpTip("Quit the terminal.");
    addCommand(static_cast<LocalInterface*>(getInterface()), &LocalInterface::quit, info);
}

void GlobalService::help_cmd(const QString &pStr)
{
//    auto command_map = mServices.getCommands();

//    for(auto iter = command_map.begin(); iter != command_map.end();)
//    {
//        if(!iter.value()->getInfo().getName().contains(pStr, Qt::CaseInsensitive))
//        {
//            iter = command_map.erase(iter);
//        }
//        else
//        {
//            ++iter;
//        }
//    }

//    if (command_map.size() == 0)
//    {
//        qio::qout << NOTHING_FOUND_MSG << endl;
//    }
//    else if(command_map.size() == 1)
//    {
//        auto command = command_map.begin().value();
//        qio::qout << command->getInfo().getName();

//        for (auto& arg: command->getInfo().getArgumentsInfo())
//        {
//            qio::qout << QString(" <%1>").arg(arg.name);
//        }

//        qio::qout << endl;

//        if(command->getInfo().hasHelpTip())
//        {
//            qio::qout << command->getInfo().getHelpTip() << endl;
//        }

//        if(command->getInfo().getArgumentsInfo().size())
//        {
//            qio::qout << left;

//            for (auto& arg: command->getInfo().getArgumentsInfo())
//            {
//                qio::qout << QString(40, '_')
//                          << endl
//                          << QString("<%1, %2> = \"%3\"")
//                             .arg(arg.name)
//                             .arg(arg.short_name)
//                             .arg(arg.default_value)
//                          << endl
//                          << arg.help_tip
//                          << endl;
//            }

//        }
//        else
//        {
//            qio::qout << WITHOUT_ARGUMENTS_MSG << endl;
//        }

//    }
//    else
//    {
//        for(auto command : command_map)
//        {
//            qio::qout << qSetFieldWidth(16)
//                      << left
//                      << command->getInfo().getName();
//            if(command->getInfo().hasHelpTip())
//            {
//                qio::qout << qSetFieldWidth(0)
//                          << " : "
//                          << command->getInfo().getHelpTip();
//            }
//            qio::qout << endl;
//        }
//    }

    //  qio::qout.flush();
}

} // UI
