#include <QStringList>
#include "command.h"

namespace UserInterface
{

Command::Command(const QString &pName,
                 const QString &pHelp,
                 const QVector<Command::ArgumentInfo> &pArgs_info,
                 ICommandAdapter* pAdapter):
    mName(pName),
    mHelp(pHelp),
    mArgs_info(pArgs_info),
    mAdapter(pAdapter)
{

}

void Command::exec(const QString &pArgs)
{
    QStringList arg_list = splitArgsLine(pArgs);
    //mAdapter->call(arg_list);
}

const QString& Command::getName() const
{
    return mName;
}

QStringList Command::splitArgsLine(const QString &pArgs_str)
{
    QStringList list;
    QString arg;
    bool escape = false;
    enum { Idle, Arg, QuotedArg } state = Idle;
    foreach (QChar const c, pArgs_str) {
        if (!escape && c == '\\') { escape = true; continue; }
        switch (state) {
        case Idle:
            if (!escape && c == '"') state = QuotedArg;
            else if (escape || !c.isSpace()) { arg += c; state = Arg; }
            break;
        case Arg:
            if (!escape && c == '"') state = QuotedArg;
            else if (escape || !c.isSpace()) arg += c;
            else { list << arg; arg.clear(); state = Idle; }
            break;
        case QuotedArg:
            if (!escape && c == '"') state = arg.isEmpty() ? Idle : Arg;
            else arg += c;
            break;
        }
        escape = false;
    }
    if (!arg.isEmpty()) list << arg;
    return list;
}

} // UserInterface
