#ifndef APPCASTENCLOSURE_H
#define APPCASTENCLOSURE_H

#include <QtCore>
#include "../../../src/xml/xml.h"


class AppcastEnclosure : public QObject,
                         public IXmlDeserializer
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
    IXmlDeserializer* deserializeXmlStartElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name);	
    void deserializeXmlAttributes(XmlReader* reader, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlReader* reader, const QStringRef & text);
    
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

#endif // APPCASTENCLOSURE_H
