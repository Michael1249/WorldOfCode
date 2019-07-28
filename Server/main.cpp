#include <QCoreApplication>
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;

    return a.exec();
}
