#include "mockupdatechecker.h"
#include "update.h"


MockUpdateChecker::MockUpdateChecker(QObject *parent /* = 0 */)
    : AbstractUpdateChecker(parent)
{
}

MockUpdateChecker::~MockUpdateChecker()
{
}

void MockUpdateChecker::check()
{
    emit finished();
}

QList<Update *> MockUpdateChecker::updates()
{
    return mUpdates;
}

void MockUpdateChecker::addUpdate(Update *update)
{
    update->setParent(this);
    mUpdates.append(update);
}
