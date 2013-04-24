#ifndef QTXUPDATE_APPCASTUPDATE_H
#define QTXUPDATE_APPCASTUPDATE_H

#include "updateglobal.h"
#include "update.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastItem;
class AppcastUpdatePrivate;

class AppcastUpdate : public Update
{
    Q_OBJECT
    
public:
    AppcastUpdate(AppcastItem *item, QObject *parent = 0);
    ~AppcastUpdate();
    
    QString title() const;
    QString version() const;
    QUrl linkUrl() const;
    QUrl releaseNotesUrl() const;
    QUrl packageUrl() const;
    QString mimeType() const;
    QString md5Sum() const;
    
    QString minSysVersion() const;
    
protected:
    AppcastUpdatePrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastUpdate);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTUPDATE_H
