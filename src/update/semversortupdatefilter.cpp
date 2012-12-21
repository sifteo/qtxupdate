#include "semversortupdatefilter.h"
#include "update.h"
#include <QtxVersion>


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
    qSort(sorted.begin(), sorted.end(), SemVerSortUpdateFilter::greaterThan);
    return sorted;
}

bool SemVerSortUpdateFilter::lessThan(const Update *u1, const Update *u2)
{
    Version v1(u1->version());
    Version v2(u2->version());
    
    return v1 < v2;
}

bool SemVerSortUpdateFilter::greaterThan(const Update *u1, const Update *u2)
{
    Version v1(u1->version());
    Version v2(u2->version());
    
    return v1 > v2;
}
