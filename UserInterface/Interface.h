#ifndef INTERFACE_H
#define INTERFACE_H

#include "CommandParser.h"

namespace UI
{

void Run();

// Singleton
class Interface
{
public:

    static Interface& getInstance();
    void run();
    const CommandParser& getParser();

private:

    Q_DISABLE_COPY_MOVE(Interface)
    Interface() = default;

    // only Command can add/remove itself to Interface
    friend class Command;

    void addCommand(const Command& pCommand);
    void removeCommand(const Command& pCommand);

    CommandParser mParser;
    bool mFlag_run_end = false;

};

} // UI

#endif // INTERFACE_H
