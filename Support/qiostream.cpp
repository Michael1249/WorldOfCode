#include "qiostream.h"

QTextStream qio::qin(stdin);
QTextStream qio::qout(stdout);

namespace qio
{
    QTextStream& info(QTextStream& stream)
    {
        stream << "\033[32m";
        return stream;
    } // green

    QTextStream& warning(QTextStream& stream)
    {
        stream << "\033[93m";
        return stream;
    }//yellow

    QTextStream& error(QTextStream& stream)
    {
        stream << "\033[33m";
        return stream;
    }//orange

    QTextStream& fatal(QTextStream& stream)
    {
        stream << "\033[31m";
        return stream;
    }// red

    QTextStream& cendl(QTextStream& stream)
    {
        stream << "\033[0m\r\n";
        stream.flush();
        return stream;
    } // Endl for color line
}
