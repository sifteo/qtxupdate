#include "semversortupdatefilter.h"
#include "update.h"
#include <QtxVersion>

QTX_BEGIN_NAMESPACE


class SemVerSortUpdateFilterPrivate
{
public:
    static bool lessThan(const Update *u1, const Update *u2);
    static bool greaterThan(const Update *u1, const Update *u2);
};


SemVerSortUpdateFilter::SemVerSortUpdateFilter(QObject *parent /* = 0 */)
    : AbstractUpdateFilter(parent)
{
}

SemVerSortUpdateFilter::~SemVerSortUpdateFilter()
{
}

QList<Update *> SemVerSortUpdateFilter::filter(const QList<Update *> candidates)
{
    QList<Update *> sorted(candidates);
    qSort(sorted.begin(), sorted.end(), SemVerSortUpdateFilterPrivate::greaterThan);
    return sorted;
}


bool SemVerSortUpdateFilterPrivate::lessThan(const Update *u1, const Update *u2)
{
    Version v1(u1->version());
    Version v2(u2->version());
    
    return v1 < v2;
}

bool SemVerSortUpdateFilterPrivate::greaterThan(const Update *u1, const Update *u2)
{
    Version v1(u1->version());
    Version v2(u2->version());
    
    return v1 > v2;
}


QTX_END_NAMESPACE
