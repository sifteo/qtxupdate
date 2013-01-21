#include "mockfailingupdatechecker.h"
#include "update.h"


MockFailingUpdateChecker::MockFailingUpdateChecker(QObject *parent /* = 0 */)
    : AbstractUpdateChecker(parent)
{
}

MockFailingUpdateChecker::~MockFailingUpdateChecker()
{
}

void MockFailingUpdateChecker::check()
{
    emit error(-1);
}

QList<Update *> MockFailingUpdateChecker::updates()
{
    return QList<Update *>();
}
