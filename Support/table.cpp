#include <algorithm>
#include "table.h"

namespace qio
{

Table::Table(const QString& pDelimeter, int pSize):
    QVector<TebleRaw> (pSize),
    mDelimeter(pDelimeter)
{

}

QTextStream &operator<<(QTextStream &pOut, const Table &pTable)
{
    QList<QPair<TebleRaw::const_iterator,TebleRaw::const_iterator>> iterator_pairs;
    QVector<int> widths;
    widths.reserve(pTable.size());

    for(auto& raw : pTable)
    {
        iterator_pairs.append({raw.begin(), raw.end()});
        widths.push_back(raw.getWidth());
    }

    bool flag_end = false;
    while (!flag_end)
    {
        flag_end = true;
        int counter = 0;
        //bool flag_to_next_line = false;
        //QStringList next_line;

        for (auto& pair: iterator_pairs)
        {
            int current_width = widths[counter];
            if(counter)
            {
                pOut << qSetFieldWidth(pTable.mDelimeter.size()) << pTable.mDelimeter;
            }

            pOut << qSetFieldWidth(current_width);
            if(pair.first != pair.second)
            {
                flag_end = false;
                ++pair.first;
                //QStringRef current_out(&(*pair.first), 0, current_width);
                //QStringRef next_line_out(&(*pair.first), current_width, pair.first->size() - current_width);

                //pOut << current_out;
            }
            else
            {

            }
            pOut << endl;
            ++counter;
        }

    }


    return pOut;
}

} // QIO
