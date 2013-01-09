#ifndef APPCASTSYSUPDATEFILTER_H
#define APPCASTSYSUPDATEFILTER_H

#include "updateglobal.h"
#include "abstractupdatefilter.h"
#include <QtxVersion>
#include <QtCore>

QTX_BEGIN_NAMESPACE


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


QTX_END_NAMESPACE

#endif // APPCASTSYSUPDATEFILTER_H
