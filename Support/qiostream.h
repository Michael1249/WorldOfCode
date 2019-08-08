#ifndef QIOSTREAM_H
#define QIOSTREAM_H

#include<QTextStream>

namespace qio
{

extern QTextStream qout;
extern QTextStream qin;



QTextStream& info(QTextStream& stream); // green
QTextStream& warning(QTextStream& stream); //yellow
QTextStream& error(QTextStream& stream); //orange
QTextStream& fatal(QTextStream& stream); // red

QTextStream& cendl(QTextStream& stream); // Endl for color line

} // QIO

#endif // QIOSTREAM_H
