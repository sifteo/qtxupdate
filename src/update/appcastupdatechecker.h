#ifndef APPCASTUPDATECHECKER_H
#define APPCASTUPDATECHECKER_H

#include <QtCore>
#include <QtNetwork>
#include "../../../src/xml/xml.h"
#include "abstractupdatechecker.h"


// Update Checker -> list of packages/versions -> compatibility checker -> single package/version -> update applyer

// Update Checker -> list of packages/versions -> filters (compatibility, skipeed version, etc) -> version comparator -> single package/version -> update applyer

class NetworkExchange;
class XmlReader;
class Update;
class AppcastItem;

class AppcastUpdateChecker : public AbstractUpdateChecker,
                             public IXmlReaderDelegate,
                             public IXmlDeserializer
{
    Q_OBJECT
    
public:
    AppcastUpdateChecker(QObject *parent = 0);
    ~AppcastUpdateChecker();
    
    void check();
    QList<Update *> updates();
    
    void setUrl(const QUrl & url);
    void setRequest(const QNetworkRequest & request);
    void setNetworkAccessManager(QNetworkAccessManager *manager);
    
signals:
    
private slots:
    void onReplyReceived();
    void onReadyRead();
    void onFinished();
    void onError(quint32 code);
    
    void onItemParsed();

private:
    IXmlDeserializer* rootXmlDeserializer(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    void xmlReadComplete(XmlReader* reader);
    void xmlReadError(XmlReader* reader, const QXmlStreamReader::Error error, const QString & errorString);
    
    IXmlDeserializer* deserializeXmlStartElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlReader* reader, const QStringRef & namespaceUri, const QStringRef & name); 
    void deserializeXmlAttributes(XmlReader* reader, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlReader* reader, const QStringRef & text);

private:
    QUrl mUrl;
    QNetworkRequest mRequest;
    NetworkExchange *mExchange;
    XmlReader* mXmlReader;
    
    QList<Update *> mUpdates;
    AppcastItem *mParsingItem;
    
    QNetworkAccessManager* mAccessManager;
    
private:
    static const char kChannelXmlElementName[];
};

#endif // APPCASTUPDATECHECKER_H
