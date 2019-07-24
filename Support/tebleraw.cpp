#include "tebleraw.h"


TebleRaw::TebleRaw(int pWidth):
    mWidth(pWidth)
{

}

int TebleRaw::getWidth() const
{
    return mWidth;
}

void TebleRaw::setWidth(int pWidth)
{
    mWidth = pWidth;
}
