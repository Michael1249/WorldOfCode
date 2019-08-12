#include "jsonviewer.h"

JsonViewer::JsonViewer()
{

}

void JsonViewer::readDoc(const QJsonObject obj)
{
    if(obj["type"].toString() == "info")
        qio::info << obj["data"].toString() << qio::messend;
    else if(obj["type"].toString() == "warning")
        qio::warning << obj["data"].toString() << qio::messend;
    else if(obj["type"].toString() == "fatal")
        qio::fatal << obj["data"].toString() << qio::messend;
    else
        qio::error << obj["data"].toString() << qio::messend;
}

void A::send(QString type, QString data)
{
    QJsonObject obj;
    obj["type"] = type;
    obj["data"] = data;

    emit signalData(obj);
}
