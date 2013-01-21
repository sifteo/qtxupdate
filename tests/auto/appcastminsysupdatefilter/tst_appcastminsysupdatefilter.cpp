#include "tst_appcastminsysupdatefilter.h"
#include "update.h"


void tst_AppcastMinSysUpdateFilter::initTestCase()
{
    mNetAccessManager = new MockNetworkAccessManager();
    mNetAccessManager->setDelegate(this);
}

void tst_AppcastMinSysUpdateFilter::cleanupTestCase()
{
    if (mNetAccessManager) {
        delete mNetAccessManager;
        mNetAccessManager = 0;
    }
}

void tst_AppcastMinSysUpdateFilter::init()
{
    mChecker = new AppcastUpdateChecker();
    mChecker->setNetworkAccessManager(mNetAccessManager);
    connect(mChecker, SIGNAL(finished()), SLOT(onFinished()));
    connect(mChecker, SIGNAL(error(qint32)), SLOT(onError(qint32)));
    
    QTimer::singleShot(10000, this, SLOT(onTimeout()));
}

void tst_AppcastMinSysUpdateFilter::cleanup()
{
    if (mChecker) {
        delete mChecker;
        mChecker = 0;
    }
}

void tst_AppcastMinSysUpdateFilter::allSystemsPass()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->setUrl(QUrl("http://www.example.com/sample.xml"));
    mChecker->check();
    mEventLoop.exec();
    
    AppcastMinSysUpdateFilter filter("");
    QList<Update *> updates = filter.filter(mChecker->updates());
    
    QCOMPARE(updates.count(), 3);
    QCOMPARE(updates.at(0)->version(), QString("2.0"));
    QCOMPARE(updates.at(1)->version(), QString("1.5"));
    QCOMPARE(updates.at(2)->version(), QString("241"));
}

void tst_AppcastMinSysUpdateFilter::only10_7orEarlierPass()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->setUrl(QUrl("http://www.example.com/sample.xml"));
    mChecker->check();
    mEventLoop.exec();
    
    AppcastMinSysUpdateFilter filter("10.7");
    QList<Update *> updates = filter.filter(mChecker->updates());
    
    QCOMPARE(updates.count(), 3);
    QCOMPARE(updates.at(0)->version(), QString("2.0"));
    QCOMPARE(updates.at(1)->version(), QString("1.5"));
    QCOMPARE(updates.at(2)->version(), QString("241"));
}

void tst_AppcastMinSysUpdateFilter::only10_6orEarlierPass()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->setUrl(QUrl("http://www.example.com/sample.xml"));
    mChecker->check();
    mEventLoop.exec();
    
    AppcastMinSysUpdateFilter filter("10.6");
    QList<Update *> updates = filter.filter(mChecker->updates());
    
    QCOMPARE(updates.count(), 3);
    QCOMPARE(updates.at(0)->version(), QString("2.0"));
    QCOMPARE(updates.at(1)->version(), QString("1.5"));
    QCOMPARE(updates.at(2)->version(), QString("241"));
}

void tst_AppcastMinSysUpdateFilter::only10_5orEarlierPass()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->setUrl(QUrl("http://www.example.com/sample.xml"));
    mChecker->check();
    mEventLoop.exec();
    
    AppcastMinSysUpdateFilter filter("10.5");
    QList<Update *> updates = filter.filter(mChecker->updates());
    
    QCOMPARE(updates.count(), 2);
    QCOMPARE(updates.at(0)->version(), QString("1.5"));
    QCOMPARE(updates.at(1)->version(), QString("241"));
}

QIODevice *tst_AppcastMinSysUpdateFilter::createIncomingData(const QNetworkRequest & req, QIODevice * outgoingData /* = 0 */)
{
    Q_UNUSED(outgoingData)

    QString path = req.url().path();
    QFile *file = 0;
    
    QString accept = QString::fromUtf8(req.rawHeader("Accept"));
    
    if ("application/rss+xml" != accept) {
        return 0;
    }
    
    if ("/sample.xml" == path) {
        file = new QFile("data/sample.http");
    }
    
    if (file) {
        file->open(QIODevice::ReadOnly);
        return file;
    }
    return 0;
}

void tst_AppcastMinSysUpdateFilter::onFinished()
{
    mEventLoop.quit();
}

void tst_AppcastMinSysUpdateFilter::onError(qint32 code)
{
    Q_UNUSED(code)

    //qDebug() << "tst_AppcastUpdateChecker::onError";
    //qDebug() << "  error: " << code;
    //qDebug() << "  string: " << mChecker->errorString();
    
    mEventLoop.quit();
}

void tst_AppcastMinSysUpdateFilter::onTimeout()
{
    mEventLoop.quit();
}


QTEST_MAIN(tst_AppcastMinSysUpdateFilter)
