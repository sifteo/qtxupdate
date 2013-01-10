#include "tst_appcastupdatechecker.h"


void tst_AppcastUpdateChecker::init()
{
    mChecker = new AppcastUpdateChecker();
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

void tst_AppcastUpdateChecker::onFinished()
{
    qDebug() << "tst_AppcastUpdateChecker::onFinished";
    
    mEventLoop.quit();
}

void tst_AppcastUpdateChecker::onError(qint32 code)
{
    qDebug() << "tst_AppcastUpdateChecker::onError";
    qDebug() << "  error: " << code;
    qDebug() << "  string: " << mChecker->errorString();
    
    mEventLoop.quit();
}

void tst_AppcastUpdateChecker::onTimeout()
{
    qDebug() << "tst_AppcastUpdateChecker::onTimeout";
    
    mEventLoop.quit();
}


QTEST_MAIN(tst_AppcastUpdateChecker)
