#include "jsonviewer.h"

JsonViewer::JsonViewer()
{

}

void JsonViewer::readDoc(const QJsonObject obj)
{
    if(obj["type"].toString() == "info")
        qio::info << obj["data"].toString() << endl;
    else if(obj["type"].toString() == "warning")
        qio::warning << obj["data"].toString() << endl;
    else if(obj["type"].toString() == "fatal")
        qio::fatal << obj["data"].toString() << endl;
    else
        qio::error << obj["data"].toString() << endl;
}

void A::send()
{
    QJsonObject obj;
    obj["type"] = "info";
    obj["data"] = "Vlad is cool";

    emit data(obj);
}
