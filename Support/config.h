#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

namespace ConfigSpace
{
    enum sendType : qint8 {FILE, COMMAND};
    const quint16 PORT = 9999;
}

#endif // CONFIG_H
