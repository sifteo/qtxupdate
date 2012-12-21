#include "semverversioncomparator.h"
#include <QtxVersion>


SemVerVersionComparator::SemVerVersionComparator(QObject *parent /* = 0 */)
  : AbstractVersionComparator(parent)
{
}

SemVerVersionComparator::~SemVerVersionComparator()
{
}

int SemVerVersionComparator::compare(const QString & lhs, const QString & rhs)
{
    Version vlhs(lhs);
    Version vrhs(rhs);
    
    return vlhs.compare(vrhs);
}
