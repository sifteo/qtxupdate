#ifndef MOCK_MOCKFAILINGUPDATECHECKER_H
#define MOCK_MOCKFAILINGUPDATECHECKER_H

#include "abstractupdatechecker.h"
#include <QtCore>

QTX_USE_NAMESPACE


class MockFailingUpdateChecker : public AbstractUpdateChecker
{
    Q_OBJECT

public:
    MockFailingUpdateChecker(QObject *parent = 0);
    ~MockFailingUpdateChecker();
    
    void check();
    QList<Update *> updates();
};

#endif // MOCK_MOCKFAILINGUPDATECHECKER_H