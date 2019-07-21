#include "interface.h"
#include "usercommand.h"

namespace UI
{
namespace API
{

UserCommand::UserCommand(std::unique_ptr<ICommandDelegate> pAdapter,
                                        const QString &pName,
                                        const QList<ArgInfo>& pSignature,
                                        const QString& pHelp_tip):
    Command (std::move(pAdapter), pName, pSignature, pHelp_tip)
{
    Interface::getInstance()->addCommand(*this);
}

UserCommand::~UserCommand()
{
    Interface::getInstance()->removeCommand(*this);
}

} // API
} // UI
