#include <QCoreApplication>
#include "UserInterface/Interface.h"
#include "UIConfig.h"
#include "qiostream.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qio::qout << qio::info << "Info" << qio::cendl;
    qio::qout << qio::warning << "Warning" << qio::cendl;
    qio::qout << qio::error << "Error" << qio::cendl;
    qio::qout << qio::fatal << "Fatal" << qio::cendl;

//    setUpUI();
//    UI::Run();

    return a.exec();
}
