#ifndef ABSTRACTVERSIONCOMPARATOR_H
#define ABSTRACTVERSIONCOMPARATOR_H

#include "updateglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AbstractVersionComparator : public QObject
{
    Q_OBJECT
    
public:
    AbstractVersionComparator(QObject *parent = 0);
    virtual ~AbstractVersionComparator();
    
    virtual int compare(const QString & lhs, const QString & rhs) = 0;
};


QTX_END_NAMESPACE

#endif // ABSTRACTVERSIONCOMPARATOR_H
