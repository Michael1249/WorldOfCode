#include <QCoreApplication>
#include "UserInterface/Interface.h"
#include "UIConfig.h"
#include "qiostream.h"

#include "jsonviewer.h"

#include <QJsonObject>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JsonViewer jv;
    A aa;

    QObject::connect(&aa, SIGNAL(signalData(QJsonObject)), &jv, SLOT(readDoc(QJsonObject)));

    aa.send("info", "data");
    aa.send("warning", "data");
    aa.send("error", "data");
    aa.send("fatal", "data");

//    setUpUI();
//    UI::Run();

       return a.exec();
}
