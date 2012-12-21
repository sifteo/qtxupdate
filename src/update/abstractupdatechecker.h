#ifndef ABSTRACTUPDATECHECKER_H
#define ABSTRACTUPDATECHECKER_H

#include <QtCore>


class Update;

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

private:
    QString mErrorString;
};

#endif // ABSTRACTUPDATECHECKER_H
