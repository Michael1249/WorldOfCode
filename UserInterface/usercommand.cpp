#include "interface.h"
#include "qiostream.h"
#include "usercommand.h"

namespace UI
{
namespace User
{

UserCommand::UserCommand(std::unique_ptr<ICommandDelegate> pAdapter,
                         const QString &pName,
                         const QList<ArgInfo>& pSignature,
                         const QString& pHelp_tip,
                         bool pTrack_enable_state):
    Command (std::move(pAdapter), pName, pSignature, pHelp_tip),
    mFlag_track_enable_state(pTrack_enable_state)
{
    Interface::getInstance()->addCommand(*this);

    if(mFlag_track_enable_state)
    {
        QIO::qout << '+' << getName() << endl;
    }

}

UserCommand::~UserCommand()
{
    Interface::getInstance()->removeCommand(*this);
    if(mFlag_track_enable_state)
    {
        QIO::qout << '-' << getName() << endl;
    }
}

void UserCommand::setEnable(bool pEnable)
{

    if(mFlag_track_enable_state)
    {

        if(isEnable() && !pEnable)
        {
            QIO::qout << '-' << getName() << endl;
        }
        else if(!isEnable() && pEnable)
        {
            QIO::qout << '+' << getName() << endl;
        }

    }

    Command::setEnable(pEnable);
}

} // API
} // UI
