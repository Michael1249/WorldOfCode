#include <iostream>
#include "command.h"

void Command::exec(const Command::args_t& pArgs)
{
    Command::arg_values_t arg_values(mArgs_info.size());

    for(size_t i = 0; i < arg_values.size(); ++i)
    {
        arg_values[i] = mArgs_info[i].default_value;
    }

    bool flag_with_name = false;
    bool flag_execute = true;
    for (auto& arg : pArgs)
    {

        if (isNamedArgument(arg))
        {
            flag_with_name = true;
            int32_t arg_pos = getArgPosition(arg);

            if (arg_pos < 0)
            {
                std::cout << "[ERROR]: invalid argument name!";
                flag_execute = false;
                break;
            }

            arg_values[static_cast<size_t>(arg_pos)] = extractValue(arg);
        }
        else if (isOptionon(arg))
        {
            flag_with_name = true;
            int32_t arg_pos = getOptionPosition(arg[1]);

            if (arg_pos < 0)
            {
                std::cout << "[ERROR]: invalid argument name!";
                flag_execute = false;
                break;
            }

            arg_values[static_cast<size_t>(arg_pos)] = extractValue(arg);
        }
        else
        {
            if(flag_with_name)
            {
                std::cout << "[ERROR]: Argument can't be unnamed after any other named!";
                flag_execute = false;
                break;
            }

        }

    }

}

const std::string& Command::getName() const
{
    return mName;
}

bool Command::isOptionon(const Command::arg_t &pArg)
{
    return pArg[0] == '-' && pArg[2] == '=';
}

bool Command::isNamedArgument(const Command::arg_t &pArg)
{
    return pArg[0] == '-' && pArg[1] == '-';
}


