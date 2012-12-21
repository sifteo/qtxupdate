#ifndef ABSTRACTUPDATEFILTER_H
#define ABSTRACTUPDATEFILTER_H

#include <QtCore>


class Update;

class AbstractUpdateFilter : public QObject
{
    Q_OBJECT
    
public:
    AbstractUpdateFilter(QObject *parent = 0);
    virtual ~AbstractUpdateFilter();
    
    virtual QList<Update *> filter(const QList<Update *> candidates) = 0;
};

#endif // ABSTRACTUPDATEFILTER_H
