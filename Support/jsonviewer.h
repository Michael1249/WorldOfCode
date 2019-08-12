#ifndef JSONVIEWER_H
#define JSONVIEWER_H

#include <QObject>
#include <QJsonObject>
#include <qiostream.h>


class JsonViewer : public QObject
{
    Q_OBJECT
public:
    JsonViewer();
public slots:
    void readDoc(const QJsonObject obj);
};

class A : public QObject
{
    Q_OBJECT
public:
    void send(QString type, QString data);
signals:
    void signalData(QJsonObject jv);
};



#endif // JSONVIEWER_H
