#ifndef APPCASTITEM_H
#define APPCASTITEM_H

#include "updateglobal.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastEnclosure;

class AppcastItem : public QObject,
                    public IXmlDeserializing
{
    Q_OBJECT
    
public:
    AppcastItem(QObject *parent = 0);
    virtual ~AppcastItem();
    
    QString title() const;
    QString version() const;
    QUrl linkUrl() const;
    const AppcastEnclosure *enclosure() const;
    QString minSystemVersion() const;
    
signals:
    void parsed();
    
private slots:
    void onEnclosureParsed();
    
private:
    IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri);	
    void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
private:
    QString mTitle;
    QString mVersion;
    QUrl mLinkUrl;
    QList<AppcastEnclosure *> mEnclosures;
    QString mMinSystemVersion;
    
    AppcastEnclosure *mParsingEnclosure;
    QString mCharacters;
    quint32 mDepth;
    
public:
    static const char kSparkleXmlNamespace[];
    static const char kXmlElementName[];
private:
    static const char kTitleXmlElementName[];
    static const char kLinkXmlElementName[];
    static const char kMinimumSystemVersionXmlElementName[];
};


QTX_END_NAMESPACE

#endif // APPCASTITEM_H
