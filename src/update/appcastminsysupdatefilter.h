#ifndef QTXUPDATE_APPCASTMINSYSUPDATEFILTER_H
#define QTXUPDATE_APPCASTMINSYSUPDATEFILTER_H

#include "updateglobal.h"
#include "abstractupdatefilter.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastMinSysUpdateFilterPrivate;

class AppcastMinSysUpdateFilter : public AbstractUpdateFilter
{
    Q_OBJECT
    
public:
    AppcastMinSysUpdateFilter(QObject *parent = 0);
    AppcastMinSysUpdateFilter(const QString & version, QObject *parent = 0);
    ~AppcastMinSysUpdateFilter();
    
    QList<Update *> filter(const QList<Update *> candidates);
    
protected:
    AppcastMinSysUpdateFilterPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastMinSysUpdateFilter);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTMINSYSUPDATEFILTER_H
