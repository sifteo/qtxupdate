#ifndef QTXUPDATE_SEMVERSORTUPDATEFILTER_H
#define QTXUPDATE_SEMVERSORTUPDATEFILTER_H

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
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_SEMVERSORTUPDATEFILTER_H
