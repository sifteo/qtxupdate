#include "semverversioncomparator.h"
#include <QtxVersion>

QTX_BEGIN_NAMESPACE


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


QTX_END_NAMESPACE
