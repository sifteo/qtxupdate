#include "tst_semversortupdatefilter.h"
#include "../../mock/src/mockupdate.h"


void tst_SemVerSortUpdateFilter::sortTest()
{
    QList<Update *> updates;
    updates.append(new MockUpdate("1.1", this));
    updates.append(new MockUpdate("1.10", this));
    updates.append(new MockUpdate("1.2", this));

    SemVerSortUpdateFilter filter;
    QList<Update *> filtered = filter.filter(updates);
    
    QCOMPARE(filtered.count(), 3);
    QCOMPARE(filtered.at(0)->version(), QString("1.10"));
    QCOMPARE(filtered.at(1)->version(), QString("1.2"));
    QCOMPARE(filtered.at(2)->version(), QString("1.1"));
}


QTEST_APPLESS_MAIN(tst_SemVerSortUpdateFilter)
