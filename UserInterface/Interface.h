#ifndef INTERFACE_H
#define INTERFACE_H

#include "CommandParser.h"
#include "UIComponent.h"
#include "Interface_source.h"

namespace UI
{

void Run();

template <class Pack_t>
void addStaticCmdPack()
{
    static Pack_t pack;
}

template <class Pack_t>
void addStaticUIComponent(QString pName, QString pHelp_tip = "")
{
    static UI::UIComponent<Pack_t> component(pName, pHelp_tip, false);
}

// Singleton
class Interface : public QObject
{
    Q_OBJECT

public:

    static Interface& getInstance();
    void run();
    const CommandParser& getParser();

public slots:
    void addCommand_slot();
    void rmCommand_slot();


private:

    Q_DISABLE_COPY_MOVE(Interface)
    Interface() = default;

    // only Command can add/remove itself to Interface
    friend class Command;

    void addCommand(const Command& pCommand, const CommandInfo& pInfo);
    void removeCommand(const QString &pCommand_name);

    CommandParser mParser;
    bool mFlag_run_end = false;

};

} // UI

#endif // INTERFACE_H
