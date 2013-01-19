#ifndef QTXUPDATE_APPCASTMINSYSTEMUPDATEFILTER_H
#define QTXUPDATE_APPCASTMINSYSTEMUPDATEFILTER_H

#include "updateglobal.h"
#include "abstractupdatefilter.h"
#include <QtxVersion>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastMinSystemUpdateFilter : public AbstractUpdateFilter
{
    Q_OBJECT
    
public:
    AppcastMinSystemUpdateFilter(QObject *parent = 0);
    ~AppcastMinSystemUpdateFilter();
    
    QList<Update *> filter(const QList<Update *> candidates);
    
private:
    static Version sysVersion();
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTMINSYSTEMUPDATEFILTER_H
