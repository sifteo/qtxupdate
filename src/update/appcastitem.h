#ifndef APPCASTITEM_H
#define APPCASTITEM_H

#include <QtCore>
#include "../../../src/xml/xml.h"


class AppcastEnclosure;

class AppcastItem : public QObject,
                    public IXmlDeserializer
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
    IXmlDeserializer* deserializeXmlStartElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name);	
    void deserializeXmlAttributes(XmlReader* reader, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlReader* reader, const QStringRef & text);
    
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

#endif // APPCASTITEM_H
