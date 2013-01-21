#include "tst_semverversioncomparator.h"
#include "../../mock/src/mockupdate.h"


void tst_SemVerVersionComparator::compareTest()
{
    SemVerVersionComparator comparator;
    
    QVERIFY(comparator.compare("1.2.2", "1.2.3") == -1);
    QVERIFY(comparator.compare("1.2.3", "1.2.3") == 0);
    QVERIFY(comparator.compare("1.2.4", "1.2.3") == 1);
}


QTEST_APPLESS_MAIN(tst_SemVerVersionComparator)
