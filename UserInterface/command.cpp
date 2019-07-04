#include "command.h"

std::string Command::exec(const Command::args_t &)
{
    return "";
}

const std::string& Command::getName() const
{
    return mName;
}
