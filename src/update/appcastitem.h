#ifndef QTXUPDATE_APPCASTITEM_H
#define QTXUPDATE_APPCASTITEM_H

#include "updateglobal.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastEnclosure;
class AppcastItemPrivate;

class AppcastItem : public QObject,
                    public IXmlDeserializing
{
    Q_OBJECT
    
public:
    static QString xmlName();
    
public:
    AppcastItem(QObject *parent = 0);
    virtual ~AppcastItem();
    
    QString title() const;
    QString version() const;
    QUrl linkUrl() const;
    const AppcastEnclosure *enclosure() const;
    QString minSystemVersion() const;
    
private:
    IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name);	
    void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
protected:
    AppcastItemPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastItem);
};


QTX_END_NAMESPACE

#endif // QTXUPDATE_APPCASTITEM_H
