#ifndef INTERFACE_H
#define INTERFACE_H

#include "commandparser.h"

namespace UserInterface
{

class Interface
{
public:
    static Interface* getInstance();
    void run();
private:
    Interface();
    Interface(const Interface&) = delete;
    Interface& operator=(Interface&) = delete;

    friend class UserCommand;
    void addCommand(const Command& pCommand);
    void removeCommand(const Command& pCommand);

    static Interface* p_instance;

    CommandParser mParser;
    bool flag_run_end = false;
};

} // UserInterface

#endif // INTERFACE_H
