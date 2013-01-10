#ifndef QTXUPDATE_ABSTRACTUPDATECHECKER_H
#define QTXUPDATE_ABSTRACTUPDATECHECKER_H

#include "updateglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class Update;
class AbstractUpdateCheckerPrivate;

class AbstractUpdateChecker : public QObject
{
    Q_OBJECT
    
public:
    AbstractUpdateChecker(QObject *parent = 0);
    virtual ~AbstractUpdateChecker();
    
    virtual void check() = 0;
    virtual QList<Update *> updates() = 0;
    
    QString errorString() const;
    
signals:
    void finished();
    void error(qint32 code);
    
protected:
    void setErrorString(const QString & str);

protected:
    AbstractUpdateCheckerPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractUpdateChecker);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_ABSTRACTUPDATECHECKER_H
