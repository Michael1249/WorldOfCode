#ifndef STDCOMMANDS_H
#define STDCOMMANDS_H

#include "QString"
#include "Command.h"

namespace UI
{

class StdCommands
{
public:

    StdCommands();

private:

    void help_request(const QString& pStr);
    Command help_request_cmd;

};

} // UI

#endif // STDCOMMANDS_H
