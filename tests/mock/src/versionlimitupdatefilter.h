#ifndef QTXUPDATE_VERSIONLIMITUPDATEFILTER_H
#define QTXUPDATE_VERSIONLIMITUPDATEFILTER_H

#include "updateglobal.h"
#include "abstractupdatefilter.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class VersionLimitUpdateFilterPrivate;

class VersionLimitUpdateFilter : public AbstractUpdateFilter
{
    Q_OBJECT
    
public:
    VersionLimitUpdateFilter(const QString & version, QObject *parent = 0);
    ~VersionLimitUpdateFilter();
    
    QList<Update *> filter(const QList<Update *> candidates);
    
protected:
    VersionLimitUpdateFilterPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(VersionLimitUpdateFilter);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_VERSIONLIMITUPDATEFILTER_H
