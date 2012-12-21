#ifndef ABSTRACTVERSIONCOMPARATOR_H
#define ABSTRACTVERSIONCOMPARATOR_H

#include <QtCore>


class AbstractVersionComparator : public QObject
{
    Q_OBJECT
    
public:
    AbstractVersionComparator(QObject *parent = 0);
    virtual ~AbstractVersionComparator();
    
    virtual int compare(const QString & lhs, const QString & rhs) = 0;
};

#endif // ABSTRACTVERSIONCOMPARATOR_H
