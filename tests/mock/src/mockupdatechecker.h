#ifndef MOCK_MOCKUPDATECHECKER_H
#define MOCK_MOCKUPDATECHECKER_H

#include "abstractupdatechecker.h"
#include <QtCore>

QTX_USE_NAMESPACE


class MockUpdateChecker : public AbstractUpdateChecker
{
    Q_OBJECT

public:
    MockUpdateChecker(QObject *parent = 0);
    ~MockUpdateChecker();
    
    void check();
    QList<Update *> updates();
    
    void addUpdate(Update *update);
    
private:
    QList<Update *> mUpdates;
};

#endif // MOCK_MOCKUPDATECHECKER_H