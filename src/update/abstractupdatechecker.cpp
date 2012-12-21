#include "abstractupdatechecker.h"


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
