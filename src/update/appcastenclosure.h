#ifndef APPCASTENCLOSURE_H
#define APPCASTENCLOSURE_H

#include "updateglobal.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastEnclosure : public QObject,
                         public IXmlDeserializing
{
    Q_OBJECT
    
public:
    AppcastEnclosure(QObject *parent = 0);
    virtual ~AppcastEnclosure();
    
    QString version() const;
    QUrl url() const;
    QString mimeType() const;
    
signals:
    void parsed();
    
private:
    IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri);	
    void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
private:
    QString mVersion;
    QUrl mUrl;
    QString mMimeType;
    
    quint32 mDepth;
    
public:
    static const char kXmlElementName[];
private:
    static const char kVersionXmlElementName[];
    static const char kUrlXmlElementName[];
    static const char kTypeXmlElementName[];
};


QTX_END_NAMESPACE

#endif // APPCASTENCLOSURE_H
