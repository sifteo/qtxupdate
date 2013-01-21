#ifndef TST_APPCASTMINSYSUPDATEFILTER_H
#define TST_APPCASTMINSYSUPDATEFILTER_H

#include "appcastupdatechecker.h"
#include "appcastminsysupdatefilter.h"
#include <QtxMockNetwork>
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_AppcastMinSysUpdateFilter : public QObject,
                                      public IMockNetworkAccessManagerDelegate
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    
    void allSystemsPass();
    void only10_7orEarlierPass();
    void only10_6orEarlierPass();
    void only10_5orEarlierPass();
    
private:
    QEventLoop mEventLoop;
    MockNetworkAccessManager *mNetAccessManager;
    AppcastUpdateChecker *mChecker;
    
public:
    QIODevice *createIncomingData(const QNetworkRequest & req, QIODevice * outgoingData = 0);
    
public slots:
    void onFinished();
    void onError(qint32 code);
    void onTimeout();
};

#endif // TST_APPCASTMINSYSUPDATEFILTER_H
