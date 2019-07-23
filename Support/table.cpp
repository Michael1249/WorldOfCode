#include <algorithm>
#include "table.h"

namespace QIO
{

Table::Table(const QString& pDelimeter, int pSize):
    QVector<TebleRaw> (pSize),
    mDelimeter(pDelimeter)
{

}

QTextStream &operator<<(QTextStream &pOut, const Table &pTable)
{
    QVector<TebleRaw::const_iterator> iters(pTable.size());
    QVector<TebleRaw::const_iterator> iters_end(pTable.size());
    std::transform(pTable.begin(), pTable.end(), iters.begin(), [](auto& raw){return raw.begin();});
    std::transform(pTable.begin(), pTable.end(), iters.begin(), [](auto& raw){return raw.end();});
    pOut << iters[0].i->t();
    bool flag_end = false;

    while (!flag_end)
    {

        for(auto iter : iters)
        {
            //pOut << *iter << pTable.mDelimeter;
        }
        pOut << endl;
        flag_end = true;
//        for (int i = 0; i < iters.size(); ++i)
//        {
//            if(iters[i] != iters_end[i])
//            {
//                flag_end = false;
//            }
//            ++iters[i];
//        }

    }

    return pOut;
}

} // QIO
