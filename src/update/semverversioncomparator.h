#ifndef SEMVERVERSIONCOMPARATOR_H
#define SEMVERVERSIONCOMPARATOR_H

#include "updateglobal.h"
#include "abstractversioncomparator.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class SemVerVersionComparator : public AbstractVersionComparator
{
    Q_OBJECT
    
public:
    SemVerVersionComparator(QObject *parent = 0);
    ~SemVerVersionComparator();
    
    int compare(const QString & lhs, const QString & rhs);
};


QTX_END_NAMESPACE

#endif // SEMVERVERSIONCOMPARATOR_H
