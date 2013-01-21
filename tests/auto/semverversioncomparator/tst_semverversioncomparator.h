#ifndef TST_SEMVERVERSIONCOMPARATOR_H
#define TST_SEMVERVERSIONCOMPARATOR_H

#include "semverversioncomparator.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_SemVerVersionComparator : public QObject
{
    Q_OBJECT

private slots:
    void compareTest();
};

#endif // TST_SEMVERVERSIONCOMPARATOR_H
