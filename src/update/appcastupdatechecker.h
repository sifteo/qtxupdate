#ifndef APPCASTUPDATECHECKER_H
#define APPCASTUPDATECHECKER_H

#include "updateglobal.h"
#include "abstractupdatechecker.h"
#include <QtxXml>
#include <QtNetwork>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class AppcastUpdateCheckerPrivate;

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
    
private slots:
    void onReplyReceived();
    void onReadyRead();
    void onFinished();
    void onError(quint32 code);

private:
    IXmlDeserializing *deserializeXmlStart(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEnd(XmlDeserializer *deserializer);
    void deserializeXmlError(XmlDeserializer *deserializer, const QXmlStreamReader::Error error, const QString & errorString);
    
    IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri, const QXmlStreamAttributes & attributes);
    void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & name, const QStringRef & namespaceUri); 
    void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);

protected:
    AppcastUpdateCheckerPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(AppcastUpdateChecker);
};


QTX_END_NAMESPACE

#endif // APPCASTUPDATECHECKER_H
