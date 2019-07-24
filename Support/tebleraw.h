#ifndef TEBLERAW_H
#define TEBLERAW_H

#include <QStringList>

class TebleRaw : public QStringList
{
public:
    TebleRaw(int pWidth = 0);
    int getWidth() const;
    void setWidth(int pWidth);
private:
    int mWidth;
};

#endif // TEBLERAW_H
