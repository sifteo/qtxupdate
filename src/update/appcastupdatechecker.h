#ifndef APPCASTUPDATECHECKER_H
#define APPCASTUPDATECHECKER_H

#include "updateglobal.h"
#include "abstractupdatechecker.h"
#include <QtxXml>
#include <QtNetwork>
#include <QtCore>

QTX_BEGIN_NAMESPACE


// Update Checker -> list of packages/versions -> compatibility checker -> single package/version -> update applyer

// Update Checker -> list of packages/versions -> filters (compatibility, skipeed version, etc) -> version comparator -> single package/version -> update applyer

class NetworkExchange;
class XmlReader;
class Update;
class AppcastItem;

class AppcastUpdateChecker : public AbstractUpdateChecker,
                             public IXmlDeserializerDelegate,
                             public IXmlDeserializing
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
    IXmlDeserializing *deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEnd(XmlDeserializer *deserializer);
    void deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString);
    
    IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri); 
    void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);

private:
    QUrl mUrl;
    QNetworkRequest mRequest;
    NetworkExchange *mExchange;
    XmlDeserializer* mXmlReader;
    
    QList<Update *> mUpdates;
    AppcastItem *mParsingItem;
    
    QNetworkAccessManager* mAccessManager;
    
private:
    static const char kChannelXmlElementName[];
};


QTX_END_NAMESPACE

#endif // APPCASTUPDATECHECKER_H
