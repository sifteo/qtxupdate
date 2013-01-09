#ifndef APPCASTUPDATE_H
#define APPCASTUPDATE_H

#include "updateglobal.h"
#include "update.h"
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastItem;

class AppcastUpdate : public Update
{
    Q_OBJECT
    
public:
    AppcastUpdate(AppcastItem *item, QObject *parent = 0);
    ~AppcastUpdate();
    
    QString name() const;
    QString version() const;
    QUrl linkUrl() const;
    QUrl packageUrl() const;
    QString mimeType() const;
    
    QString minSystemVersion() const;
    
private:
    AppcastItem *mItem;
};


QTX_END_NAMESPACE

#endif // APPCASTUPDATE_H
