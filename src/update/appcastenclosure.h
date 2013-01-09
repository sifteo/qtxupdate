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
    
    
    IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri);	
    void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
protected:
    AppcastEnclosurePrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastEnclosure);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTENCLOSURE_H
