#ifndef UPDATERESOLVER_H
#define UPDATERESOLVER_H

#include "updateglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AbstractUpdateChecker;
class AbstractVersionComparator;
class AbstractUpdateFilter;
class Update;

class UpdateResolver : public QObject
{
    Q_OBJECT
    
public:
    typedef enum {
        UnknownError        = 0,
        InvalidCheckerError = 1,
    } Error;
    
public:
    UpdateResolver(QObject *parent = 0);
    ~UpdateResolver();
    
    void resolve();
    void resolve(const QString & version);
    Update *updateFrom(const QString & version);
    
    void setChecker(AbstractUpdateChecker *checker);
    void setComparator(AbstractVersionComparator *comparator);
    void addFilter(AbstractUpdateFilter *filter);
    
signals:
    void updateAvailable(Update *);
    void noUpdateAvailable();
    void error(UpdateResolver::Error code);
    
private slots:
    void onCheckerFinished();
    void onCheckerError(qint32 code);

private:
    QString mVersion;
    
    AbstractUpdateChecker *mChecker;
    AbstractVersionComparator *mComparator;
    QList<AbstractUpdateFilter *> mFilters;
};


QTX_END_NAMESPACE

#endif // UPDATERESOLVER_H
