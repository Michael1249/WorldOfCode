#ifndef INTERFACE_H
#define INTERFACE_H

#include "commandparser.h"

namespace UI
{
namespace User
{
class Interface
{
public:
    static Interface* getInstance();
    void run();
    const CommandParser& getParser();
private:
    friend class UserCommand;

    Interface() = default;
    Interface(const Interface&) = delete;
    Interface& operator=(Interface&) = delete;

    void addCommand(const Command& pCommand);
    void removeCommand(const Command& pCommand);

    CommandParser mParser;
    bool mFlag_run_end = false;
};

void Run();

} // API
} // UI

#endif // INTERFACE_H
