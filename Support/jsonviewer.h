#ifndef JSONVIEWER_H
#define JSONVIEWER_H

#include <QObject>
#include <QJsonObject>
#include <qiostream.h>


class JsonViewer : QObject
{
    Q_OBJECT
public:
    JsonViewer();
private slots:
    void readDoc(const QJsonObject obj);

};

#endif // JSONVIEWER_H
