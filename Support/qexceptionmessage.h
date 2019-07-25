#ifndef QMESSAGEEXCEPTION_H
#define QMESSAGEEXCEPTION_H

#include <QException>
#include <QString>

class QExceptionMessage : public QException
{
public:
    QExceptionMessage(const QString& pMessage);

    const QString& getMessage();

    void raise() const override;
    QExceptionMessage *clone() const override;

private:
    const QString mMessage;

};

#endif // QMESSAGEEXCEPTION_H
