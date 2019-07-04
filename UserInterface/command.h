#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command
{
public:
    using args_t = std::vector<std::string>;

    Command() = default;

    const std::string& exec(const args_t&);
    const std::string& getName() const;

private:
    std::string mName;
};

#endif // COMMAND_H
