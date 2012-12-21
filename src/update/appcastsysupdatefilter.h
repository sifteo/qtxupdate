#ifndef APPCASTSYSUPDATEFILTER_H
#define APPCASTSYSUPDATEFILTER_H

#include <QtCore>
#include <QtxVersion>
#include "abstractupdatefilter.h"


class AppcastSysUpdateFilter : public AbstractUpdateFilter
{
    Q_OBJECT
    
public:
    AppcastSysUpdateFilter(QObject *parent = 0);
    ~AppcastSysUpdateFilter();
    
    QList<Update *> filter(const QList<Update *> candidates);
    
private:
    static Version sysVersion();
};

#endif // APPCASTSYSUPDATEFILTER_H
