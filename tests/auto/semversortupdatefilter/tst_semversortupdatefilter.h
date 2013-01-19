#ifndef TST_SEMVERSORTUPDATEFILTER_H
#define TST_SEMVERSORTUPDATEFILTER_H

#include "semversortupdatefilter.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_SemVerSortUpdateFilter : public QObject
{
    Q_OBJECT

private slots:
    void sortTest();
};

#endif // TST_SEMVERSORTUPDATEFILTER_H
