#ifndef SEMVERSORTUPDATEFILTER_H
#define SEMVERSORTUPDATEFILTER_H

#include "abstractupdatefilter.h"
#include <QtCore>


class SemVerSortUpdateFilter : public AbstractUpdateFilter
{
    Q_OBJECT
    
public:
    SemVerSortUpdateFilter(QObject *parent = 0);
    ~SemVerSortUpdateFilter();
    
    QList<Update *> filter(const QList<Update *> candidates);
    
    static bool lessThan(const Update *u1, const Update *u2);
    static bool greaterThan(const Update *u1, const Update *u2);
};

#endif // SEMVERSORTUPDATEFILTER_H
