#ifndef QTXUPDATE_ABSTRACTVERSIONCOMPARATOR_H
#define QTXUPDATE_ABSTRACTVERSIONCOMPARATOR_H

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

#endif // QTXUPDATE_ABSTRACTVERSIONCOMPARATOR_H
