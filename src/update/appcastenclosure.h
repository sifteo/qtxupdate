#ifndef QTXUPDATE_APPCASTENCLOSURE_H
#define QTXUPDATE_APPCASTENCLOSURE_H

#include "updateglobal.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastEnclosurePrivate;

class AppcastEnclosure : public QObject,
                         public IXmlDeserializing
{
    Q_OBJECT
    
public:
    static QString xmlName();
    
public:
    AppcastEnclosure(QObject *parent = 0);
    virtual ~AppcastEnclosure();
    
    QString version() const;
    QUrl url() const;
    QString mimeType() const;
    QString md5Sum() const;
    
    
    void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    
protected:
    AppcastEnclosurePrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastEnclosure);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTENCLOSURE_H
