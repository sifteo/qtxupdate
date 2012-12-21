#ifndef UPDATE_H
#define UPDATE_H

#include <QtCore>


class Update : public QObject
{
    Q_OBJECT
    
public:
    Update(QObject *parent = 0);
    virtual ~Update();
    
    virtual QString name() const = 0;
    virtual QString version() const = 0;
    virtual QUrl linkUrl() const = 0;
    virtual QUrl packageUrl() const = 0;
    virtual QString mimeType() const = 0;
};

#endif // UPDATE_H
