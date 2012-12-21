#ifndef APPCASTUPDATE_H
#define APPCASTUPDATE_H

#include <QtCore>
#include "update.h"


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

#endif // APPCASTUPDATE_H
