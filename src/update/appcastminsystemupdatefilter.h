#ifndef QTXUPDATE_APPCASTMINSYSTEMUPDATEFILTER_H
#define QTXUPDATE_APPCASTMINSYSTEMUPDATEFILTER_H

#include "updateglobal.h"
#include "abstractupdatefilter.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastMinSystemUpdateFilterPrivate;

class AppcastMinSystemUpdateFilter : public AbstractUpdateFilter
{
    Q_OBJECT
    
public:
    AppcastMinSystemUpdateFilter(QObject *parent = 0);
    AppcastMinSystemUpdateFilter(const QString & systemVersion, QObject *parent = 0);
    ~AppcastMinSystemUpdateFilter();
    
    QList<Update *> filter(const QList<Update *> candidates);
    
protected:
    AppcastMinSystemUpdateFilterPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastMinSystemUpdateFilter);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTMINSYSTEMUPDATEFILTER_H
