#include <QCoreApplication>
#include "UserInterface/Interface.h"
#include "UIConfig.h"
#include "qiostream.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qio::info << "Learn, you never die! But you always can try." << qio::messend;


//    setUpUI();
//    UI::Run();

       return a.exec();
}
