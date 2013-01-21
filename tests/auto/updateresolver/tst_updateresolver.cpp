#include "tst_updateresolver.h"
#include "../../mock/src/mockupdatechecker.h"
#include "../../mock/src/mockupdate.h"


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

void tst_UpdateResolver::updateFromTest()
{
    Update *update = 0;

    MockUpdateChecker *checker = new MockUpdateChecker();
    checker->addUpdate(new MockUpdate("1.8"));
    checker->addUpdate(new MockUpdate("1.7"));
    mResolver->setChecker(checker);
    
    
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
    mResolver->setChecker(checker);
    
    
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
    mResolver->setChecker(checker);
    
    
    update = mResolver->updateFrom("");
    QVERIFY(update == 0);
    
    delete checker;
}


QTEST_APPLESS_MAIN(tst_UpdateResolver)
