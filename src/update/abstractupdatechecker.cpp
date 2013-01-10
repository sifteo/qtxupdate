#include "abstractupdatechecker.h"

QTX_BEGIN_NAMESPACE


class AbstractUpdateCheckerPrivate
{
public:
    QString errorString;
};


AbstractUpdateChecker::AbstractUpdateChecker(QObject *parent /* = 0 */)
    : QObject(parent),
      d_ptr(new AbstractUpdateCheckerPrivate())
{
}

AbstractUpdateChecker::~AbstractUpdateChecker()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = 0;
    }
}

QString AbstractUpdateChecker::errorString() const
{
    return d_ptr->errorString;
}

void AbstractUpdateChecker::setErrorString(const QString & str)
{
    d_ptr->errorString = str;
}


QTX_END_NAMESPACE
