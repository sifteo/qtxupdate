#ifndef TST_APPCASTMINSYSTEMUPDATEFILTER_H
#define TST_APPCASTMINSYSTEMUPDATEFILTER_H

#include "appcastupdatechecker.h"
#include "appcastminsystemupdatefilter.h"
#include <QtxMockNetwork>
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_AppcastMinSystemUpdateFilter : public QObject,
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

#endif // TST_APPCASTMINSYSTEMUPDATEFILTER_H
