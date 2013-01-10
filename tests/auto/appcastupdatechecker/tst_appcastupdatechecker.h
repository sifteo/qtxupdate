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
    
    void unconfiguredUrl();
    
private:
    QEventLoop mEventLoop;
    //MockNetworkAccessManager* _netAccessManager;
    AppcastUpdateChecker *mChecker;
    
public slots:
    void onFinished();
    void onError(qint32 code);
    void onTimeout();
};

#endif // TST_APPCASTUPDATECHECKER_H
