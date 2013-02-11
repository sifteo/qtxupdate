#ifndef UPDATERESOLVER_H
#define UPDATERESOLVER_H

#include "updateglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AbstractUpdateChecker;
class AbstractVersionComparator;
class AbstractUpdateFilter;
class Update;
class UpdateResolverPrivate;

class UpdateResolver : public QObject
{
    Q_OBJECT
    
public:
    typedef enum {
        NoError             = 0,
        InvalidCheckerError = 1,
        UnknownCheckError   = 2
    } Error;
    
public:
    UpdateResolver(QObject *parent = 0);
    ~UpdateResolver();
    
    void resolve();
    void resolve(const QString & version);
    Update *updateFrom(const QString & version);
    
    void setUpdateChecker(AbstractUpdateChecker *checker);
    void addUpdateFilter(AbstractUpdateFilter *filter);
    void setVersionComparator(AbstractVersionComparator *comparator);
    
    QString errorString() const;
    
signals:
    void updateAvailable(Update *);
    void updateNotAvailable();
    void error(UpdateResolver::Error code);
    
protected:
    void setErrorString(const QString & str);
    
private slots:
    void onCheckerFinished();
    void onCheckerError(qint32 code);
    
protected:
    UpdateResolverPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(UpdateResolver);
};


QTX_END_NAMESPACE

#endif // UPDATERESOLVER_H
