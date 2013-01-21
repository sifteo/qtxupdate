#include "tst_updateresolver.h"
#include "../../mock/src/mockupdatechecker.h"
#include "../../mock/src/mockfailingupdatechecker.h"
#include "../../mock/src/mockupdate.h"
#include "../../mock/src/versionlimitupdatefilter.h"


void tst_UpdateResolver::initTestCase()
{
    qRegisterMetaType<Update *>("Update *");
    qRegisterMetaType<int>("UpdateResolver::Error");
}

void tst_UpdateResolver::init()
{
    mResolver = new UpdateResolver();
}

void tst_UpdateResolver::cleanup()
{
    if (mResolver) {
        delete mResolver;
        mResolver = 0;
    }
}

void tst_UpdateResolver::resolveTest()
{
    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("1.8"));
    checker->addUpdate(new MockUpdate("1.7"));
    mResolver->setUpdateChecker(checker);
    
    
    QSignalSpy updateAvailableSpy(mResolver, SIGNAL(updateAvailable(Update *)));
    QSignalSpy noUpdateAvailableSpy(mResolver, SIGNAL(noUpdateAvailable()));
    QSignalSpy errorSpy(mResolver, SIGNAL(error(UpdateResolver::Error)));
    
    mResolver->resolve("1.6");
    
    QVERIFY(updateAvailableSpy.count() == 1);
    QVERIFY(noUpdateAvailableSpy.count() == 0);
    QVERIFY(errorSpy.count() == 0);
    
    QList<QVariant> arguments;
    Update *update = 0;
    
    arguments = updateAvailableSpy.takeFirst();
    update = arguments.at(0).value<Update *>();
    QCOMPARE(update->version(), QString("1.8"));
    
    delete checker;
}

void tst_UpdateResolver::resolveNoUpdateTest()
{
    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("1.6"));
    checker->addUpdate(new MockUpdate("1.5"));
    mResolver->setUpdateChecker(checker);
    
    
    QSignalSpy updateAvailableSpy(mResolver, SIGNAL(updateAvailable(Update *)));
    QSignalSpy noUpdateAvailableSpy(mResolver, SIGNAL(noUpdateAvailable()));
    QSignalSpy errorSpy(mResolver, SIGNAL(error(UpdateResolver::Error)));
    
    mResolver->resolve("1.6");
    
    QVERIFY(updateAvailableSpy.count() == 0);
    QVERIFY(noUpdateAvailableSpy.count() == 1);
    QVERIFY(errorSpy.count() == 0);
    
    delete checker;
}

void tst_UpdateResolver::resolveErrorTest()
{
    MockFailingUpdateChecker *checker = new MockFailingUpdateChecker();
    mResolver->setUpdateChecker(checker);

    QSignalSpy updateAvailableSpy(mResolver, SIGNAL(updateAvailable(Update *)));
    QSignalSpy noUpdateAvailableSpy(mResolver, SIGNAL(noUpdateAvailable()));
    QSignalSpy errorSpy(mResolver, SIGNAL(error(UpdateResolver::Error)));
    
    mResolver->resolve("1.6");
    
    QVERIFY(updateAvailableSpy.count() == 0);
    QVERIFY(noUpdateAvailableSpy.count() == 0);
    QVERIFY(errorSpy.count() == 1);
    
    QList<QVariant> arguments = errorSpy.takeFirst();
    QVERIFY(arguments.at(0).toInt() == UpdateResolver::UnknownCheckError);
}

void tst_UpdateResolver::resolveInvalidCheckerError()
{
    QSignalSpy updateAvailableSpy(mResolver, SIGNAL(updateAvailable(Update *)));
    QSignalSpy noUpdateAvailableSpy(mResolver, SIGNAL(noUpdateAvailable()));
    QSignalSpy errorSpy(mResolver, SIGNAL(error(UpdateResolver::Error)));
    
    mResolver->resolve("1.6");
    
    QVERIFY(updateAvailableSpy.count() == 0);
    QVERIFY(noUpdateAvailableSpy.count() == 0);
    QVERIFY(errorSpy.count() == 1);
    
    QList<QVariant> arguments = errorSpy.takeFirst();
    QVERIFY(arguments.at(0).toInt() == UpdateResolver::InvalidCheckerError);
}

void tst_UpdateResolver::updateFromTest()
{
    Update *update = 0;

    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("1.8"));
    checker->addUpdate(new MockUpdate("1.7"));
    mResolver->setUpdateChecker(checker);
    
    
    update = mResolver->updateFrom("2.0");
    QVERIFY(update == 0);
    
    update = mResolver->updateFrom("1.6");
    QVERIFY(update != 0);
    QCOMPARE(update->version(), QString("1.8"));
    
    delete checker;
}

void tst_UpdateResolver::updateFromWithNoUpdatesTest()
{
    Update *update = 0;

    MockUpdateChecker *checker = new MockUpdateChecker();
    mResolver->setUpdateChecker(checker);
    
    
    update = mResolver->updateFrom("1.6");
    QVERIFY(update == 0);
    
    delete checker;
}

void tst_UpdateResolver::updateFromInvalidVersionTest()
{
    Update *update = 0;

    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("1.8"));
    checker->addUpdate(new MockUpdate("1.7"));
    mResolver->setUpdateChecker(checker);
    
    
    update = mResolver->updateFrom("");
    QVERIFY(update == 0);
    
    delete checker;
}

void tst_UpdateResolver::updateFromInvalidCheckerTest()
{
    Update *update = 0;
    
    update = mResolver->updateFrom("1.6");
    QVERIFY(update == 0);
}

void tst_UpdateResolver::filterTest()
{
    Update *update = 0;

    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("3.0"));
    checker->addUpdate(new MockUpdate("2.1"));
    checker->addUpdate(new MockUpdate("2.0"));
    checker->addUpdate(new MockUpdate("1.8"));
    checker->addUpdate(new MockUpdate("1.7"));
    mResolver->setUpdateChecker(checker);
    mResolver->addUpdateFilter(new VersionLimitUpdateFilter("3.0"));
    
    update = mResolver->updateFrom("1.6");
    QVERIFY(update != 0);
    QCOMPARE(update->version(), QString("2.1"));
    
    delete checker;
}

void tst_UpdateResolver::multipleFilterTest()
{
    Update *update = 0;

    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("3.0"));
    checker->addUpdate(new MockUpdate("2.1"));
    checker->addUpdate(new MockUpdate("2.0"));
    checker->addUpdate(new MockUpdate("1.8"));
    checker->addUpdate(new MockUpdate("1.7"));
    mResolver->setUpdateChecker(checker);
    mResolver->addUpdateFilter(new VersionLimitUpdateFilter("3.0"));
    mResolver->addUpdateFilter(new VersionLimitUpdateFilter("2.0"));
    
    update = mResolver->updateFrom("1.6");
    QVERIFY(update != 0);
    QCOMPARE(update->version(), QString("1.8"));
    
    delete checker;
}


QTEST_APPLESS_MAIN(tst_UpdateResolver)
