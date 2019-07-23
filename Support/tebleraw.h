#ifndef TEBLERAW_H
#define TEBLERAW_H

#include <QStringList>

class TebleRaw : public QStringList
{
public:
    TebleRaw(size_t pWidth = 0);

private:
    size_t mWidth;
};

#endif // TEBLERAW_H
