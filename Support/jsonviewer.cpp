#include "jsonviewer.h"

JsonViewer::JsonViewer()
{

}

void JsonViewer::readDoc(const QJsonObject obj)
{
    if(obj["type"].toString() == "info")
}
