#ifndef SEMVERSORTUPDATEFILTER_H
#define SEMVERSORTUPDATEFILTER_H

#include "updateglobal.h"
#include "abstractupdatefilter.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


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


QTX_END_NAMESPACE

#endif // SEMVERSORTUPDATEFILTER_H
