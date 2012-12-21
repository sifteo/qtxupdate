#ifndef SEMVERVERSIONCOMPARATOR_H
#define SEMVERVERSIONCOMPARATOR_H

#include "abstractversioncomparator.h"
#include <QtCore>


class SemVerVersionComparator : public AbstractVersionComparator
{
    Q_OBJECT
    
public:
    SemVerVersionComparator(QObject *parent = 0);
    ~SemVerVersionComparator();
    
    int compare(const QString & lhs, const QString & rhs);
};

#endif // SEMVERVERSIONCOMPARATOR_H
