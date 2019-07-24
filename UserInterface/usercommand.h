#ifndef USERCOMMAND_H
#define USERCOMMAND_H

#include "command.h"

namespace UI
{
namespace User
{


class UserCommand: public Command
{
public:
    UserCommand(std::unique_ptr<ICommandDelegate> pAdapter,
                const QString& pName,
                const QList<ArgInfo>& pSignature = {},
                const QString& pHelp_tip = "",
                bool pTrack_enable_state = true);
    ~UserCommand();

    void setEnable(bool pEnable);

private:
    bool mFlag_track_enable_state;
};

} // API
} // UI

#endif // USERCOMMAND_H
