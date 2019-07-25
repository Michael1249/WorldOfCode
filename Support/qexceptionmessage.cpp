#include "qexceptionmessage.h"

QExceptionMessage::QExceptionMessage(const QString &pMessage):
    mMessage(pMessage)
{
}

const QString &QExceptionMessage::getMessage()
{
    return mMessage;
}

void QExceptionMessage::raise() const
{
    throw *this;
}

QExceptionMessage *QExceptionMessage::clone() const
{
    return new QExceptionMessage(*this);
}
