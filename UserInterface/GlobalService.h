#ifndef GLOBALSERVICE_H
#define GLOBALSERVICE_H

#include "ServiceBase.h"

namespace UI
{
class LocalInterface;
class GlobalService : public ServiceBase
{
    friend class LocalInterface;

    GlobalService(LocalInterface* interface);

    // commands
    void help_cmd(const QString& pStr);

    void init_help_cmd();
    void init_sync_cmd();
    void init_quit_cmd();
};

} // UI

#endif // GLOBALSERVICE_H
