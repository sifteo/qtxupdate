#ifndef TST_APPCASTUPDATECHECKER_H
#define TST_APPCASTUPDATECHECKER_H

#include "appcastupdatechecker.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_AppcastUpdateChecker : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    
private:
    //AppcastUpdateChecker *mChecker;
};

#endif // TST_APPCASTUPDATECHECKER_H
