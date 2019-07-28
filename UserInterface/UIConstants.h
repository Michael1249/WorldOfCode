#ifndef UICONSTANTS_H
#define UICONSTANTS_H

#include <QString>

namespace
{

const QString INIT_CMD_NAME = "init";
const QString EXIT_CMD_NAME = "exit";
const QString INIT_CMD_HELP_TIP = "Initiates %1 UI component. %2";
const QString EXIT_CMD_HELP_TIP = "Terminate %1 UI component. %2";
const QString INIT_CMD_DISABLE_REASON = "Component already init";
const QString EXIT_CMD_DISABLE_REASON = "Component already exit";
const QString UIC_INIT_MSG = "++";
const QString UIC_EXIT_MSG = "--";
const QString CMD_INIT_MSG = "+";
const QString CMD_EXIT_MSG = "-";
const QString CMD_DISABLE_REASON = "command disabled!";
const QString ERR_UNKNOWN_ARG = "Unknown argument name <%1>!";
const QString ERR_INVALID_ARG = "Positional argument \"%1\" must be placed before nemed argument(s)!";
const QString ERR_TOO_MANY_ARGS = "Too many positionaal arguments! Maximum number of arguments - %1.";
const QString ERR_UNCNOWN_CMD = "Uncnown command!";
const QString DEFAULT_INPUT = ">>>";
const QString NOTHING_FOUND_MSG = "Nothing found.";
const QString WITHOUT_ARGUMENTS_MSG = "Without arguments.";
const QString ERR_CMD_REDEFINE = "Command with name \'%1\' already exist!";

}

#endif // UICONSTANTS_H