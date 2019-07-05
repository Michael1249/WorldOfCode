#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command
{
public:
    using arg_t = std::string;
    using args_t = std::vector<arg_t>;
    using arg_values_t = std::vector<std::string>;

    Command() = default;

    void exec(const args_t& pArgs);
    const std::string& getName() const;

private:
    std::string mName;

    struct ArgumentInfo
    {
        std::string name;
        char option_name;
        std::string help;
        std::string default_value;
    };

    std::vector<ArgumentInfo> mArgs_info;

    bool isOptionon(const arg_t& pArg);
    bool isNamedArgument(const arg_t& pArg);
    int32_t getArgPosition(const arg_t& pArg);
    int32_t getOptionPosition(char pOpt);
    std::string extractValue(const arg_t& pArg);
};

#endif // COMMAND_H
