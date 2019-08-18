#ifndef QIOSTREAM_H
#define QIOSTREAM_H

#include<QTextStream>

namespace qio
{
extern QTextStream qout;
extern QTextStream qin;

QTextStream& green(QTextStream& stream);        // green
QTextStream& yellow(QTextStream& stream);       // yellow
QTextStream& orange(QTextStream& stream);       // orange
QTextStream& red(QTextStream& stream);          // red

QTextStream& endc(QTextStream& stream);         // set standard color
QTextStream& cendl(QTextStream& stream);        // endl for color line
}

namespace
{

using namespace qio;

class BaseMessage
{
protected:
    unsigned short counter = 0;
public:
    void resetCounter() { counter = 0; }
};

class Info : BaseMessage
{
public:
    template<class T>
    Info& operator<<(T data);
    void operator<< (void (*m)(BaseMessage&) ) { m(*this); }
};

template<class T>
class Info& Info::operator<<(T data)
{
    qout << green;
    if(counter == 0)
    {
        qout << "[INFO]: " << data;
        counter++;
    } else qout << data;

    qout << "\033[0m";
    qout.flush();

    return *this;
}

class Warning : BaseMessage
{
public:
    template<class T>
    Warning& operator<<(T data);
    void operator<<(void (*m)(BaseMessage&) ) { m(*this); }
};

template<class T>
class Warning& Warning::operator<< (T data)
{
    qout << yellow << "[Warning]: " << data << "\033[0m";
    qout.flush();
    return *this;
}

class Error : BaseMessage
{
public:
    template<class T>
    Error& operator<<(T data);
    void operator<< (void (*m)(BaseMessage&) ) { m(*this); }
};

template<class T>
class Error& Error::operator<< (T data)
{
    qout << orange << "[Error]: " << data << "\033[0m";
    qout.flush();
    return *this;
}

class Fatal : BaseMessage
{
public:
    template<class T>
    Fatal& operator<<(T data);
    void operator<< (void (*m)(BaseMessage&) ) { m(*this); }
};

template<class T>
class Fatal& Fatal::operator<< (T data)
{
    qout << red << "[Fatal]: " << data << "\033[0m";
    qout.flush();
    return *this;
}

}

namespace qio
{
    void messend(BaseMessage& obj)
    {
        qout << endl;
        obj.resetCounter();
    }

    ::Info info;
    ::Warning warning;
    ::Error error;
    ::Fatal fatal;
} // QIO

#endif // QIOSTREAM_H
