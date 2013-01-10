#include "tst_appcastupdatechecker.h"
#include "update.h"


void tst_AppcastUpdateChecker::initTestCase()
{
    mNetAccessManager = new MockNetworkAccessManager();
    mNetAccessManager->setDelegate(this);
}

void tst_AppcastUpdateChecker::cleanupTestCase()
{
    if (mNetAccessManager) {
        delete mNetAccessManager;
        mNetAccessManager = 0;
    }
}

void tst_AppcastUpdateChecker::init()
{
    mChecker = new AppcastUpdateChecker();
    mChecker->setNetworkAccessManager(mNetAccessManager);
    connect(mChecker, SIGNAL(finished()), SLOT(onFinished()));
    connect(mChecker, SIGNAL(error(qint32)), SLOT(onError(qint32)));
    
    QTimer::singleShot(10000, this, SLOT(onTimeout()));
}

void tst_AppcastUpdateChecker::cleanup()
{
    if (mChecker) {
        delete mChecker;
        mChecker = 0;
    }
}

void tst_AppcastUpdateChecker::sampleUpdates()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->setUrl(QUrl("http://www.example.com/sample.xml"));
    mChecker->check();
    mEventLoop.exec();
    
    
    QVERIFY(finishedSpy.count() == 1);
    QVERIFY(errorSpy.count() == 0);
    QCOMPARE(mChecker->updates().count(), 3);
    QCOMPARE(mChecker->updates().at(0)->version(), QString("2.0"));
    QCOMPARE(mChecker->updates().at(1)->version(), QString("1.5"));
    QCOMPARE(mChecker->updates().at(2)->version(), QString("241"));
}

void tst_AppcastUpdateChecker::plainTextResponse()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->setUrl(QUrl("http://www.example.com/plain-text.txt"));
    mChecker->check();
    mEventLoop.exec();
    
    
    QVERIFY(finishedSpy.count() == 0);
    QVERIFY(errorSpy.count() == 1);
    arguments = errorSpy.takeFirst();
    QVERIFY(arguments.at(0).toInt() != 0);
}

void tst_AppcastUpdateChecker::unconfiguredUrl()
{
    QSignalSpy finishedSpy(mChecker, SIGNAL(finished()));
    QSignalSpy errorSpy(mChecker, SIGNAL(error(qint32)));
    QList<QVariant> arguments;

    mChecker->check();
    mEventLoop.exec();
    

    QVERIFY(finishedSpy.count() == 0);
    QVERIFY(errorSpy.count() == 1);
    arguments = errorSpy.takeFirst();
    QVERIFY(arguments.at(0).toInt() != 0);
}

QIODevice *tst_AppcastUpdateChecker::createIncomingData(const QNetworkRequest & req)
{
    QString path = req.url().path();
    QFile *file = 0;
    
    if ("/sample.xml" == path) {
        file = new QFile("data/sample.http");
    } else if ("/plain-text.txt" == path) {
        file = new QFile("data/plain-text.http");
    }
    
    if (file) {
        file->open(QIODevice::ReadOnly);
        return file;
    }
    return 0;
}

void tst_AppcastUpdateChecker::onFinished()
{
    mEventLoop.quit();
}

void tst_AppcastUpdateChecker::onError(qint32 code)
{
    Q_UNUSED(code)

    //qDebug() << "tst_AppcastUpdateChecker::onError";
    //qDebug() << "  error: " << code;
    //qDebug() << "  string: " << mChecker->errorString();
    
    mEventLoop.quit();
}

void tst_AppcastUpdateChecker::onTimeout()
{
    mEventLoop.quit();
}


QTEST_MAIN(tst_AppcastUpdateChecker)
