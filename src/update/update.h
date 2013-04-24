#ifndef QTXUPDATE_UPDATE_H
#define QTXUPDATE_UPDATE_H

#include "updateglobal.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class Update : public QObject
{
    Q_OBJECT
    
public:
    Update(QObject *parent = 0);
    virtual ~Update();
    
    virtual QString title() const;
    virtual QString version() const = 0;
    virtual QUrl linkUrl() const;
    virtual QUrl releaseNotesUrl() const;
    virtual QUrl packageUrl() const = 0;
    virtual QString mimeType() const;
    virtual QString md5Sum() const;
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_UPDATE_H
