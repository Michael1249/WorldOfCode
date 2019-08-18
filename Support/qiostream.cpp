#include "qiostream.h"

QTextStream qio::qin(stdin);
QTextStream qio::qout(stdout);

namespace qio
{
    QTextStream& green(QTextStream& stream)
    {
        stream << "\033[32m";
        return stream;
    } // green

    QTextStream& yellow(QTextStream& stream)
    {
        stream << "\033[93m";
        return stream;
    }//yellow

    QTextStream& orange(QTextStream& stream)
    {
        stream << "\033[33m";
        return stream;
    }//orange

    QTextStream& red(QTextStream& stream)
    {
        stream << "\033[31m";
        return stream;
    }// red

    QTextStream& cendl(QTextStream& stream)
    {
        stream << "\033[0m\r\n";
        stream.flush();
        return stream;
    }

    QTextStream &endc(QTextStream &stream)
    {
        stream << "\033[0m";
        return stream;
    }


    // Endl for color line
}
