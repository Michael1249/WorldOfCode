#ifndef TABLE_H
#define TABLE_H

#include <QVector>
#include <QTextStream>
#include "tebleraw.h"

namespace QIO
{

class Table : public QVector<TebleRaw>
{
public:
    Table(const QString& pDelimeter, int size);
    friend QTextStream& operator<<(QTextStream& pOut, const Table& pTable);
private:
    QString mDelimeter;
};

} // QIO

#endif // TABLE_H
