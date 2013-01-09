#include "abstractupdatechecker.h"

QTX_BEGIN_NAMESPACE


AbstractUpdateChecker::AbstractUpdateChecker(QObject *parent /* = 0 */)
  : QObject(parent)
{
}

AbstractUpdateChecker::~AbstractUpdateChecker()
{
}

QString AbstractUpdateChecker::errorString() const
{
    return mErrorString;
}

void AbstractUpdateChecker::setErrorString(const QString & str)
{
    mErrorString = str;
}


QTX_END_NAMESPACE
