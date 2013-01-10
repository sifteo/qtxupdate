#ifndef TST_APPCASTUPDATECHECKER_H
#define TST_APPCASTUPDATECHECKER_H

#include "appcastupdatechecker.h"
#include <QtxMockNetwork>
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_AppcastUpdateChecker : public QObject,
                                 public IMockNetworkAccessManagerDelegate
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    
    void sampleUpdates();
    void sampleUpdatesWithUserAgent();
    
    void plainTextResponse();
    
    void unconfiguredUrl();
    
private:
    QEventLoop mEventLoop;
    MockNetworkAccessManager *mNetAccessManager;
    AppcastUpdateChecker *mChecker;
    
public:
    QIODevice *createIncomingData(const QNetworkRequest & req);
    
public slots:
    void onFinished();
    void onError(qint32 code);
    void onTimeout();
};

#endif // TST_APPCASTUPDATECHECKER_H
